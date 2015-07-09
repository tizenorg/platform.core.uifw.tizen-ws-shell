#include "tzsh_private.h"
#include "tzsh_quickpanel_service.h"

TZSH_SERVICE_BASE_DATA(quickpanel)
TZSH_SERVICE_BASE_IMPL(quickpanel)

TZSH_EXPORT int
tzsh_quickpanel_service_content_region_set(tzsh_quickpanel_service_h service, unsigned int angle, tzsh_region_h region)
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

TZSH_EXPORT int
tzsh_quickpanel_service_handler_region_set(tzsh_quickpanel_service_h service, unsigned int angle, tzsh_region_h region)
{
   if (!service)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   if (!region)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   if (!tzsh_service_region_set(service, TZSH_SERVICE_REGION_TYPE_HANDLER,
                                angle, region))
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   TZSH_ERR_SUCCESS_RET;
}
