#include "tzsh_private.h"
#include "tzsh_indicator_service.h"

TZSH_SERVICE_BASE_DATA(indicator)
TZSH_SERVICE_BASE_IMPL(indicator)

TZSH_EXPORT int
tzsh_indicator_service_content_region_set(tzsh_indicator_service_h service, unsigned int angle, tzsh_region_h region)
{
   if (!service)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   if (!region)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   if (!tzsh_service_region_set(service, TZSH_SERVICE_REGION_TYPE_CONTENT,
                                angle, region))
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   TZSH_ERR_SUCCESS_RET;
}

int
tzsh_indicator_service_property_change_cb_set(tzsh_indicator_service_h service, tzsh_indicator_service_cb cb_func, void *data)
{
   (void)service;
   (void)cb_func;
   (void)data;

   TZSH_ERR_SUCCESS_RET;
}
