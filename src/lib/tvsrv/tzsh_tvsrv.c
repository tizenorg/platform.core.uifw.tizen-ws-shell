#include "tzsh_private.h"
#include "tzsh_tvsrv.h"

TZSH_USER_BASE_DATA(tvsrv)
TZSH_USER_BASE_IMPL(tvsrv)

TZSH_EXPORT int
tzsh_tvsrv_bind(tzsh_tvsrv_h ts)
{
   if (!ts)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_tvsrv_bind(ts->res);
   tzsh_flush(ts->tzsh);

   TZSH_ERR_SUCCESS_RET;
}
