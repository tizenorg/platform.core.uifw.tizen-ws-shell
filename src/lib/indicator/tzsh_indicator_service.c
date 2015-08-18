#include "tzsh_protect.h"
#include "tzsh_indicator_service.h"

struct private_data
{
   struct tws_service_indicator *tws_service_indicator;
   struct
   {
      tzsh_indicator_service_cb func;
      void *data;
   } cb;
};

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

static void
_tws_service_indicator_cb_property_change(void *data, struct tws_service_indicator *tws_service_indicator, int32_t angle, int32_t opacity)
{
   tzsh_indicator_service_h service = data;
   struct private_data *pd;

   if (!service)
     return;

   pd = service->private_data;
   if (!pd)
     return;

   if (pd->cb.func)
     pd->cb.func(pd->cb.data, service, angle, opacity);
}

static const struct tws_service_indicator_listener _tws_service_indicator_listener =
{
   _tws_service_indicator_cb_property_change
};

static void
_tzsh_service_cb_destroy(void *data)
{
   tzsh_service_h service = data;
   struct private_data *pd;

   if (!service)
     return;

   if (!(pd = service->private_data))
     return;

   if (pd->tws_service_indicator)
     tws_service_indicator_destroy(pd->tws_service_indicator);

   free(pd);
}

TZSH_EXPORT int
tzsh_indicator_service_property_change_cb_set(tzsh_indicator_service_h service, tzsh_indicator_service_cb cb_func, void *data)
{
   struct private_data *pd;

   if (!(pd = service->private_data))
     {
        pd = calloc(1, sizeof(struct private_data));
        if (!pd)
          TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);

        pd->tws_service_indicator =
           tws_service_indicator_get(service->tws_service);
        if (!pd->tws_service_indicator)
          {
             free(pd);
             TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);
          }

        tzsh_service_destroy_callback_add(service, _tzsh_service_cb_destroy, service);

        tws_service_indicator_set_user_data(pd->tws_service_indicator, pd);

        service->private_data = pd;
     }

   pd->cb.func = cb_func;
   pd->cb.data = data;

   tws_service_indicator_add_listener(pd->tws_service_indicator,
                                      &_tws_service_indicator_listener, service);

   TZSH_ERR_SUCCESS_RET;
}
