#include "tzsh_private.h"
#include "tzsh_screensaver_manager_service.h"

struct private_data
{
   struct tws_service_screensaver_manager *tws_srv_scrsaver_mng;
   struct
     {
        tzsh_screensaver_manager_service_cb func;
        void *data;
     } cb;
};

TZSH_SERVICE_BASE_IMPL(screensaver_manager)

static void
_tws_srv_scrsaver_mng_cb_idle(void *data, struct tws_service_screensaver_manager *tws_srv_scrsaver_mng)
{
   tzsh_screensaver_manager_service_h service = data;
   struct private_data *pd;

   if (!service) return;

   pd = service->private_data;
   if (!pd) return;
   if (!pd->cb.func) return;

   pd->cb.func(pd->cb.data, service,
               TZSH_SCREENSAVER_MANAGER_SERVICE_STATE_IDLE_TIMEOUT_EXPIRED);
}

static void
_tws_srv_scrsaver_mng_cb_active(void *data, struct tws_service_screensaver_manager *tws_srv_scrsaver_mng)
{
   tzsh_screensaver_manager_service_h service = data;
   struct private_data *pd;

   if (!service) return;

   pd = service->private_data;
   if (!pd) return;
   if (!pd->cb.func) return;

   pd->cb.func(pd->cb.data,
               service,
               TZSH_SCREENSAVER_MANAGER_SERVICE_STATE_NOT_IDLE);
}

static const struct tws_service_screensaver_manager_listener _tws_srv_scrsaver_mng_listener =
{
   _tws_srv_scrsaver_mng_cb_idle,
   _tws_srv_scrsaver_mng_cb_active
};

static void
_tzsh_srv_cb_destroy(void *data)
{
   tzsh_service_h service = data;
   struct private_data *pd;

   if (!service) return;
   if (!(pd = service->private_data)) return;

   if (pd->tws_srv_scrsaver_mng)
     tws_service_screensaver_manager_destroy(pd->tws_srv_scrsaver_mng);

   free(pd);
}

static struct private_data *
_tzsh_srv_private_data_get(tzsh_screensaver_manager_service_h service)
{
   struct private_data *pd = NULL;

   if (!(pd = service->private_data))
     {
        pd = calloc(1, sizeof(struct private_data));
        if (!pd) return NULL;

        pd->tws_srv_scrsaver_mng = tws_service_screensaver_manager_get(service->tws_service);
        if (!pd->tws_srv_scrsaver_mng)
          {
             free(pd);
             return NULL;
          }

        tzsh_service_destroy_callback_add(service, _tzsh_srv_cb_destroy, service);
        tws_service_screensaver_manager_set_user_data(pd->tws_srv_scrsaver_mng, pd);
        service->private_data = pd;

        tws_service_screensaver_manager_add_listener(pd->tws_srv_scrsaver_mng,
                                                     &_tws_srv_scrsaver_mng_listener,
                                                     service);
     }

   return pd;
}

TZSH_EXPORT int
tzsh_screensaver_manager_service_enable(tzsh_screensaver_manager_service_h service)
{
   struct private_data *pd;

   if (!service) TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   pd = _tzsh_srv_private_data_get(service);
   if (!pd) TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);

   tws_service_screensaver_manager_enable(pd->tws_srv_scrsaver_mng);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_screensaver_manager_service_disable(tzsh_screensaver_manager_service_h service)
{
   struct private_data *pd;

   if (!service) TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   pd = _tzsh_srv_private_data_get(service);
   if (!pd) TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);

   tws_service_screensaver_manager_disable(pd->tws_srv_scrsaver_mng);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_screensaver_manager_service_state_change_cb_set(tzsh_screensaver_manager_service_h service, tzsh_screensaver_manager_service_cb cb_func, void *data)
{
   struct private_data *pd;

   if (!service) TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   pd = _tzsh_srv_private_data_get(service);
   if (!pd) TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);

   pd->cb.func = cb_func;
   pd->cb.data = data;

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_screensaver_manager_service_idle_timeout_set(tzsh_screensaver_manager_service_h service, unsigned int time)
{
   struct private_data *pd;

   if (!service) TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   pd = _tzsh_srv_private_data_get(service);
   if (!pd) TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);

   tws_service_screensaver_manager_idle_time_set(pd->tws_srv_scrsaver_mng, time);

   TZSH_ERR_SUCCESS_RET;
}
