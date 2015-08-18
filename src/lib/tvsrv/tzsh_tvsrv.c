#include "tzsh_private.h"
#include "tzsh_tvsrv.h"

TZSH_USER_BASE_DATA(tvsrv)

static void
_tzsh_tvsrv_destroy_internal(tzsh_tvsrv_h tvsrv)
{
   if (!tvsrv)
     return;

   tws_tvsrv_release((tvsrv)->res);
   tzsh_flush((tvsrv)->tzsh);
   free(tvsrv);
}

static void
_tzsh_tvsrv_cb_destroy(void *data)
{
   tzsh_tvsrv_h tvsrv = data;
   _tzsh_tvsrv_destroy_internal(tvsrv);
}

TZSH_EXPORT tzsh_tvsrv_h
tzsh_tvsrv_create(tzsh_h tzsh, tzsh_window win)
{
   tzsh_tvsrv_h tvsrv;
   struct tizen_ws_shell *tws;

   if (!tzsh)
     {
        TZSH_LAST_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);
        return NULL;
     }

   tws = tzsh_tws_get(tzsh);
   if (!tws)
     {
        TZSH_LAST_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);
        return NULL;
     }

   /* DO NOT check if service exists
    *
    *   if (!tzsh_service_exist_check(tzsh, "tvsrv"))
    *     {
    *        ERR("*%s* service is NOT EXISTED", "tvsrv");
    *        TZSH_LAST_ERR_SET(TZSH_ERROR_SERVICE_NOT_EXSITED);
    *        return NULL;
    *     }
    */

   tvsrv = calloc(1, sizeof(struct _tzsh_tvsrv_s));
   if (!tvsrv)
     {
        TZSH_LAST_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);
        return NULL;
     }

   tvsrv->res = tizen_ws_shell_tvsrv_get(tws, win);
   tvsrv->win = win;
   tvsrv->tzsh = tzsh;
   tzsh_destroy_callback_add(tzsh, _tzsh_tvsrv_cb_destroy, tvsrv);
   tzsh_flush(tzsh);
   TZSH_ERR_SUCCESS_SET;
   return tvsrv;
}

TZSH_EXPORT int
tzsh_tvsrv_destroy(tzsh_tvsrv_h tvsrv)
{
   if (!tvsrv)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
   tzsh_destroy_callback_remove((tvsrv)->tzsh,
                                _tzsh_tvsrv_cb_destroy, tvsrv);
   _tzsh_tvsrv_destroy_internal(tvsrv);
   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_tvsrv_bind(tzsh_tvsrv_h tvsrv)
{
   if (!tvsrv)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_tvsrv_bind(tvsrv->res);
   tzsh_flush(tvsrv->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_tvsrv_unbind(tzsh_tvsrv_h tvsrv)
{
   if (!tvsrv)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_tvsrv_unbind(tvsrv->res);
   tzsh_flush(tvsrv->tzsh);

   TZSH_ERR_SUCCESS_RET;
}
