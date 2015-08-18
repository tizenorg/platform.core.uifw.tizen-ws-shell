#include "tzsh_protect.h"
#include "tzsh_private.h"

struct destroy_callback_data
{
   tzsh_service_destroy_cb func;
   struct wl_list link;
   void *data;
};

TZSH_EXPORT tzsh_service_h
tzsh_service_create(tzsh_h tzsh, tzsh_window window, char *name)
{
   tzsh_service_h service;
   struct tizen_ws_shell *tws;

   if (!tzsh)
     return NULL;

   tws = tzsh_tws_get(tzsh);
   if (!tws)
     return NULL;

   service = calloc(1, sizeof *service);
   if (!service)
     return NULL;

   service->tws_service = tizen_ws_shell_service_create(tws, window, name);
   if (!service->tws_service)
     {
        free(service);
        return NULL;
     }

   service->tzsh = tzsh;
   service->window = window;

   wl_list_init(&service->destroy_cb_list);

   tzsh_flush(tzsh);

   return service;
}

TZSH_EXPORT void
tzsh_service_destroy(tzsh_service_h service)
{
   struct destroy_callback_data *cb_data = NULL, *cb_data_tmp = NULL;

   if (!service)
     return;

   if (service->destroy_cb_list.prev)
     {
        wl_list_for_each_safe(cb_data, cb_data_tmp, &service->destroy_cb_list, link)
          {
             cb_data->func(cb_data->data);
             wl_list_remove(&cb_data->link);
             free(cb_data);
          }
     }

   tws_service_destroy(service->tws_service);

   // flush the tws event before free.
   tzsh_flush(service->tzsh);

   free(service);
}

TZSH_EXPORT int
tzsh_service_region_set(tzsh_service_h service, int type, unsigned int angle, tzsh_region_h region)
{
   struct tws_region *tws_region;

   if (!service)
     return 0;

   tws_region = tzsh_tws_region_get(region);
   if (!tws_region)
     return 0;

   tws_service_region_set(service->tws_service, type, angle, tws_region);

   tzsh_flush(service->tzsh);

   return 1;
}

TZSH_EXPORT void
tzsh_service_destroy_callback_add(tzsh_service_h service, tzsh_service_destroy_cb func, void *data)
{
   struct destroy_callback_data *cb_data;

   if (!service)
     return;

   if (!func)
     return;

   cb_data = calloc(1, sizeof(struct destroy_callback_data));
   if (!cb_data)
     return;

   cb_data->func = func;
   cb_data->data = data;

   wl_list_insert(service->destroy_cb_list.prev, &cb_data->link);
}
