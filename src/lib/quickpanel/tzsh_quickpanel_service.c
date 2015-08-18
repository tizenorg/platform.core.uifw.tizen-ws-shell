#include "tzsh_protect.h"
#include "tzsh_quickpanel_service.h"

struct private_data
{
   struct tws_service_quickpanel *tws_service_quickpanel;
};

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

static void
_tzsh_service_cb_destroy(void *data)
{
   tzsh_service_h service = data;
   struct private_data *pd;

   if (!service)
     return;

   if (!(pd = service->private_data))
     return;

   if (pd->tws_service_quickpanel)
     tws_service_quickpanel_destroy(pd->tws_service_quickpanel);

   free(pd);
}

static struct private_data *
_tzsh_quickpanel_private_data_get(tzsh_quickpanel_service_h service)
{
   struct private_data *pd;

   if (!(pd = service->private_data))
     {
        pd = calloc(1, sizeof(struct private_data));
        if (!pd)
          return NULL;

        pd->tws_service_quickpanel =
           tws_service_quickpanel_get(service->tws_service);
        if (!pd->tws_service_quickpanel)
          {
             free(pd);
             return NULL;
          }

        tws_service_quickpanel_set_user_data(pd->tws_service_quickpanel, pd);

        service->private_data = pd;

        tzsh_service_destroy_callback_add(service, _tzsh_service_cb_destroy, service);
     }

   return pd;
}

TZSH_EXPORT int
tzsh_quickpanel_service_show(tzsh_quickpanel_service_h service)
{
   struct private_data *pd;

   pd = _tzsh_quickpanel_private_data_get(service);
   if (!pd)
     TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);

   tws_service_quickpanel_msg_send(pd->tws_service_quickpanel,
                                   TWS_SERVICE_QUICKPANEL_MSG_SHOW);

   tzsh_flush(service->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_service_hide(tzsh_quickpanel_service_h service)
{
   struct private_data *pd;

   pd = _tzsh_quickpanel_private_data_get(service);
   if (!pd)
     TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);

   tws_service_quickpanel_msg_send(pd->tws_service_quickpanel,
                                   TWS_SERVICE_QUICKPANEL_MSG_HIDE);

   tzsh_flush(service->tzsh);

   TZSH_ERR_SUCCESS_RET;
}
