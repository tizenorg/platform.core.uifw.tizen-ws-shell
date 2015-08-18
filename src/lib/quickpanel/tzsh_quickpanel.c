#include "tzsh_protect.h"
#include "tzsh_quickpanel.h"

TZSH_USER_BASE_DATA(quickpanel)
TZSH_USER_BASE_IMPL(quickpanel)

TZSH_EXPORT int
tzsh_quickpanel_show(tzsh_quickpanel_h qp)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_quickpanel_show(qp->res);
   tzsh_flush(qp->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_hide(tzsh_quickpanel_h qp)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_quickpanel_hide(qp->res);
   tzsh_flush(qp->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_enable(tzsh_quickpanel_h qp)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_quickpanel_enable(qp->res);
   tzsh_flush(qp->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_disable(tzsh_quickpanel_h qp)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_quickpanel_disable(qp->res);
   tzsh_flush(qp->tzsh);

   TZSH_ERR_SUCCESS_RET;
}
