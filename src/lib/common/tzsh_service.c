#include "tzsh_private.h"

struct _tzsh_service_s
{
   tzsh_h tzsh;
   struct tws_service *tws_service;
   tzsh_window window;
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

   tzsh_flush(tzsh);

   return service;
}

TZSH_EXPORT void
tzsh_service_destroy(tzsh_service_h service)
{
   if (!service)
     return;

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
