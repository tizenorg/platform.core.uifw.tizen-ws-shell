#include "config.h"
#include "tzsh_private.h"

#include <Ecore.h>

#ifdef HAVE_ECORE_WAYLAND
#include <Ecore_Wayland.h>
#endif

typedef struct _tzsh_efl_backend_data
{
   Ecore_Fd_Handler *fd_handler;
   Ecore_Idle_Enterer *idle_enterer;
} tzsh_efl_backend_data;

static Eina_Bool
_tzsh_efl_cb_handle_data(void *data, Ecore_Fd_Handler *hdl)
{
   tzsh_h tzsh = data;
   int ret = 0;

   if (ecore_main_fd_handler_active_get(hdl, ECORE_FD_ERROR))
     {
        ERR("recieived error on wayland display fd");
        return ECORE_CALLBACK_CANCEL;
     }

   if (ecore_main_fd_handler_active_get(hdl, ECORE_FD_READ))
     ret = wl_display_dispatch(tzsh->disp);
   else if (ecore_main_fd_handler_active_get(hdl, ECORE_FD_WRITE))
     {
        ret = wl_display_flush(tzsh->disp);
        if (ret == 0)
          ecore_main_fd_handler_active_set(hdl, ECORE_FD_READ);
     }

   if ((ret < 0) && ((errno != EAGAIN) && (errno != EINVAL)))
     return ECORE_CALLBACK_CANCEL;

   return ECORE_CALLBACK_RENEW;
}

static Eina_Bool
_tzsh_efl_cb_idle_enterer(void *data)
{
   tzsh_h tzsh = data;
   tzsh_efl_backend_data *backend_data;
   int ret = 0;

   ret = wl_display_get_error(tzsh->disp);
   if (ret < 0) goto err;

   ret = wl_display_dispatch_pending(tzsh->disp);
   if (ret < 0) goto err;

   ret = wl_display_flush(tzsh->disp);
   if ((ret < 0) && (errno == EAGAIN))
     {
        backend_data = tzsh->backend_data;
        ecore_main_fd_handler_active_set(backend_data->fd_handler,
                                         (ECORE_FD_READ | ECORE_FD_WRITE));
        return ECORE_CALLBACK_RENEW;
     }

err:
   if ((ret < 0) && ((errno != EAGAIN) && (errno != EINVAL)))
     {
        int _errno = errno;
        char buffer[1024];
        strerror_r(_errno, buffer, sizeof(buffer));
        ERR("wayland socket error:(%d) %s", _errno, buffer);
        return ECORE_CALLBACK_CANCEL;
     }

   return ECORE_CALLBACK_RENEW;
}

tzsh_h
tzsh_efl_create(void)
{
   tzsh_h tzsh;
   tzsh_efl_backend_data *backend_data;
   struct wl_display *display = NULL;
   int fd;

   if (!ecore_init())
     {
        ERR("failed to init ecore");
        return NULL;
     }

#ifdef HAVE_ECORE_WAYLAND
   if (!ecore_wl_init(NULL))
     {
        ERR("");
        ecore_shutdown();
        return NULL;
     }

   display = ecore_wl_display_get();
   if (!display)
     {
        ERR("");
        ecore_wl_shutdown();
        ecore_shutdown();
        return NULL;
     }
#endif

   tzsh = tzsh_create_internal(display);

   if ((tzsh) && (!display))
     {
        backend_data = calloc(1, sizeof(tzsh_efl_backend_data));
        fd = wl_display_get_fd(tzsh->disp);
        backend_data->fd_handler =
           ecore_main_fd_handler_add(fd,
                                     ECORE_FD_READ | ECORE_FD_WRITE | ECORE_FD_ERROR,
                                     _tzsh_efl_cb_handle_data, tzsh,
                                     NULL, NULL);
        backend_data->idle_enterer =
           ecore_idle_enterer_add(_tzsh_efl_cb_idle_enterer, tzsh);

        tzsh->backend_data = backend_data;
     }

   // If HAVE_ECORE_WAYLAND is not defined, pass NULL
   return tzsh;
}

void
tzsh_efl_destroy(tzsh_h tzsh)
{
   tzsh_efl_backend_data *backend_data;

   if (!tzsh)
     return;

   backend_data = tzsh->backend_data;
   if (backend_data)
     {
        if (backend_data->fd_handler)
          ecore_main_fd_handler_del(backend_data->fd_handler);
        if (backend_data->idle_enterer)
          ecore_idle_enterer_del(backend_data->idle_enterer);

        free(backend_data);
     }

   tzsh_destroy_internal(tzsh);

#ifdef HAVE_ECORE_WAYLAND
   ecore_wl_shutdown();
#endif

   ecore_shutdown();
}
