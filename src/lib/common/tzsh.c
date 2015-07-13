#include "tzsh_private.h"
#include "tzsh_efl.h"

typedef struct _Tzsh_Service_Data Tzsh_Service_Data;
typedef struct _Tzsh_Destroy_Cb_Data Tzsh_Destroy_Cb_Data;

struct _tzsh_s
{
   struct wl_display *disp;
   struct wl_registry *registry;
   struct wl_list destroy_cb_list;
   struct wl_list registered_service_list;
   struct tizen_ws_shell *tws;

   tzsh_toolkit_type_e toolkit_type;
   unsigned char disp_owned: 1;
};

struct _Tzsh_Service_Data
{
   struct wl_list link;
   char *name;
};

struct _Tzsh_Destroy_Cb_Data
{
   void *data;
   tzsh_destroy_cb func;
   struct wl_list link;
};

__thread int tzsh_last_error;

static void
_tizen_ws_shell_cb_service_register(void *data, struct tizen_ws_shell *tws, const char *name)
{
   tzsh_h tzsh = data;
   Tzsh_Service_Data *sd;
   int len;

   INF("Registered service: '%s'", name);

   if (!tzsh) return;

   sd = calloc(1, sizeof(Tzsh_Service_Data));
   if (!sd)
     return;

   len = strlen(name);
   sd->name = malloc(sizeof(char) * len);
   if (!sd->name)
     {
        free(sd);
        return;
     }

   strncpy(sd->name, name, len);
   wl_list_insert(tzsh->registered_service_list.prev, &sd->link);
}

static void
_tizen_ws_shell_cb_service_remove(void *data, struct tizen_ws_shell *tws, const char *name)
{
   tzsh_h tzsh = data;
   Tzsh_Service_Data *sd = NULL, *tmp = NULL;
   int len;

   INF("Removed service: '%s'", name);

   if (!tzsh) return;

   if (!tzsh->registered_service_list.prev)
     return;

   len = strlen(name);
   wl_list_for_each_safe(sd, tmp, &tzsh->registered_service_list, link)
     {
        if (!strncmp(sd->name, name, len))
          {
             wl_list_remove(&sd->link);
             free(sd->name);
             free(sd);
          }
     }
}

static const struct tizen_ws_shell_listener _tizen_ws_shell_listener =
{
   _tizen_ws_shell_cb_service_register,
   _tizen_ws_shell_cb_service_remove
};

static void
_tzsh_cb_global(void *data, struct wl_registry *registry, unsigned int id, const char *interface, unsigned int version)
{
   tzsh_h tzsh = data;

   if (!strcmp(interface, "tizen_ws_shell"))
     {
        INF("Bind '%s'", "tizen_ws_shell");
        tzsh->tws = wl_registry_bind(registry, id, &tizen_ws_shell_interface, 1);
        tizen_ws_shell_add_listener(tzsh->tws, &_tizen_ws_shell_listener, tzsh);
     }
}

static void
_tzsh_cb_global_remove(void *data, struct wl_registry *registry, unsigned int id)
{
   (void)data;
   (void)registry;
   (void)id;
}

static const struct wl_registry_listener _tzsh_registry_listener =
{
   _tzsh_cb_global,
   _tzsh_cb_global_remove
};

void
tzsh_destroy_internal(tzsh_h tzsh)
{
   Tzsh_Destroy_Cb_Data *cb_data = NULL, *cb_data_tmp = NULL;
   Tzsh_Service_Data *sd = NULL, *sd_tmp = NULL;

   if (tzsh->destroy_cb_list.prev)
     {
        wl_list_for_each_safe(cb_data, cb_data_tmp, &tzsh->destroy_cb_list, link)
          {
             cb_data->func(cb_data->data);
             wl_list_remove(&cb_data->link);
             free(cb_data);
          }
     }

   if (tzsh->registered_service_list.prev)
     {
        wl_list_for_each_safe(sd, sd_tmp, &tzsh->registered_service_list, link)
          {
             wl_list_remove(&sd->link);
             free(sd->name);
             free(sd);
          }
     }

   if (tzsh->tws)
     tizen_ws_shell_destroy(tzsh->tws);

   if (tzsh->registry)
     wl_registry_destroy(tzsh->registry);

   tzsh_flush(tzsh);

   if (tzsh->disp_owned)
     wl_display_disconnect(tzsh->disp);

   free(tzsh);
}

tzsh_h
tzsh_create_internal(struct wl_display *display)
{
   tzsh_h tzsh;
   const char *name = NULL;

   tzsh = calloc(1, sizeof(struct _tzsh_s));
   if (!tzsh) return NULL;

   if (!display)
     {
        name = getenv("TZSH_SOCKET");

        // if TZSH_SOCKET is not set, pass NULL argument as a socket name.
        tzsh->disp = wl_display_connect(name);

        if (!tzsh->disp)
          {
             ERR("Failed to connect Tizen Shell Server: %m");
             goto err;
          }

        tzsh->disp_owned = 1;
     }
   else
     tzsh->disp = display;

   tzsh->registry = wl_display_get_registry(tzsh->disp);
   wl_registry_add_listener(tzsh->registry, &_tzsh_registry_listener, tzsh);

   // To bind tws interface.
   if (wl_display_roundtrip(tzsh->disp) < 0)
     {
        ERR("Failed to process wayland connection: %m");
        goto err;
     }

   if (!tzsh->tws)
     {
        ERR("Failed to bind tizen window system shell");
        goto err;
     }

   // must initialize the registered_serivce_list before invoke 2nd roundtrip.
   // will be used callback.
   wl_list_init(&tzsh->registered_service_list);

   // To get registered service from server.
   if (wl_display_roundtrip(tzsh->disp) < 0)
     {
        ERR("Failed to process wayland connection: %m");
        goto err;
     }

   wl_list_init(&tzsh->destroy_cb_list);

   return tzsh;

err:
   tzsh_destroy_internal(tzsh);

   return NULL;
}

TZSH_EXPORT bool
tzsh_service_exist_check(tzsh_h tzsh, const char *name)
{
   Tzsh_Service_Data *sd;
   int len;

   if (!tzsh)
     return false;

   wl_display_dispatch_pending(tzsh->disp);

   len = strlen(name);
   wl_list_for_each(sd, &tzsh->registered_service_list, link)
     {
        if (!strncmp(sd->name, name, len))
          return true;
     }

   return false;
}

TZSH_EXPORT void
tzsh_destroy_callback_add(tzsh_h tzsh, tzsh_destroy_cb func, void *data)
{
   Tzsh_Destroy_Cb_Data *cb_data;

   if (!tzsh)
     return;

   if (!func)
     return;

   cb_data = calloc(1, sizeof(Tzsh_Destroy_Cb_Data));
   if (!cb_data)
     return;

   cb_data->func = func;
   cb_data->data = data;

   wl_list_insert(tzsh->destroy_cb_list.prev, &cb_data->link);
}

TZSH_EXPORT void
tzsh_destroy_callback_remove(tzsh_h tzsh, tzsh_destroy_cb func, void *data)
{
   Tzsh_Destroy_Cb_Data *cb_data = NULL, *tmp = NULL;

   if (!tzsh)
     return;

   if (!func)
     return;

   wl_list_for_each_safe(cb_data, tmp, &tzsh->destroy_cb_list, link)
     {
        if ((cb_data->func == func) &&
            (cb_data->data == data))
          {
             wl_list_remove(&cb_data->link);
             free(cb_data);
             break;
          }
     }
}

TZSH_EXPORT int
tzsh_get_fd(tzsh_h tzsh)
{
   if (!tzsh)
     {
        ERR("");
        return -1;
     }

   if (!tzsh->disp_owned)
     {
        ERR("display is not disp_owned by tzsh.\n"
            "Use display_get_fd()");
        return -1;
     }

   return wl_display_get_fd(tzsh->disp);
}

TZSH_EXPORT int
tzsh_dispatch(tzsh_h tzsh)
{
   if (!tzsh)
     {
        ERR("");
        return -1;
     }

   if (!tzsh->disp_owned)
     {
        ERR("display is not disp_owned by tzsh.\n"
            "Use display_dispatch()");
        return -1;
     }

   return wl_display_dispatch(tzsh->disp);
}

TZSH_EXPORT struct tizen_ws_shell *
tzsh_tws_get(tzsh_h tzsh)
{
   if (!tzsh)
     return NULL;

   return tzsh->tws;
}

TZSH_EXPORT void
tzsh_flush(tzsh_h tzsh)
{
   if (!tzsh)
     {
        ERR("");
        return;
     }

   if (!tzsh->disp_owned)
     {
        ERR("display is not disp_owned by tzsh.\n"
            "Use wl_display_flush() directly");
        return;
     }

   wl_display_flush(tzsh->disp);
}

TZSH_EXPORT tzsh_h
tzsh_create(tzsh_toolkit_type_e type)
{
   tzsh_h tzsh;

   switch (type)
     {
      case TZSH_TOOLKIT_TYPE_UNKNOWN:
         tzsh = tzsh_create_internal(NULL);
         break;

      case TZSH_TOOLKIT_TYPE_EFL:
         tzsh = tzsh_efl_create();
         break;

      default:
         TZSH_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);
         return NULL;
     }

   if (!tzsh)
     {
        TZSH_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);
        return NULL;
     }

   tzsh->toolkit_type = type;

   return tzsh;
}

TZSH_EXPORT int
tzsh_destroy(tzsh_h tzsh)
{
   if (!tzsh)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   switch (tzsh->toolkit_type)
     {
      case TZSH_TOOLKIT_TYPE_EFL:
         tzsh_efl_destroy(tzsh);
         TZSH_ERR_SUCCESS_RET;
      default:
      case TZSH_TOOLKIT_TYPE_UNKNOWN:
         // DO NOTHING
         break;
     }

   tzsh_destroy_internal(tzsh);

   TZSH_ERR_SUCCESS_RET;
}

