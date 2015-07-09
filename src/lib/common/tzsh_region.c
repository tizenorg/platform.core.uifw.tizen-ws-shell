#include <tzsh_private.h>
#include "tzsh_region.h"

struct _tzsh_region_s
{
   tzsh_h tzsh;
   struct tws_region *res;
};

TZSH_EXPORT tzsh_region_h
tzsh_region_create(tzsh_h tzsh)
{
   tzsh_region_h region;
   struct tizen_ws_shell *tws;

   if (!tzsh)
     {
        TZSH_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);
        return NULL;
     }

   if (!(tws = tzsh_tws_get(tzsh)))
     {
        TZSH_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);
        return NULL;
     }

   region = calloc(1, sizeof(struct _tzsh_region_s));
   if (!region)
     {
        TZSH_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);
        return NULL;
     }

   region->tzsh = tzsh;
   region->res = tizen_ws_shell_region_create(tws);
   if (!region->res)
     {
        free(region);
        TZSH_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);
        return NULL;
     }

   tzsh_flush(tzsh);

   TZSH_ERR_SUCCESS;
   return region;
}

TZSH_EXPORT int
tzsh_region_destroy(tzsh_region_h region)
{
   if (!region)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_region_destroy(region->res);
   tzsh_flush(region->tzsh);

   free(region);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_region_add(tzsh_region_h region, int x, int y, int w, int h)
{
   if (!region)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_region_add(region->res, x, y, w, h);

   tzsh_flush(region->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_region_subtract(tzsh_region_h region, int x, int y, int w, int h)
{
   if (!region)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_region_subtract(region->res, x, y, w, h);

   tzsh_flush(region->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT struct tws_region *
tzsh_tws_region_get(tzsh_region_h region)
{
   if (!region)
     return NULL;

   return region->res;
}
