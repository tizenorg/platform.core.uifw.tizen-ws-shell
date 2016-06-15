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
tzsh_quickpanel_visible_get(tzsh_quickpanel_h qp,
                            tzsh_quickpanel_visible_state_e *vis)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   /* TODO */

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

TZSH_EXPORT int
tzsh_quickpanel_scrollable_set(tzsh_quickpanel_h qp)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_quickpanel_enable(qp->res);
   tzsh_flush(qp->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_scrollable_unset(tzsh_quickpanel_h qp)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   tws_quickpanel_disable(qp->res);
   tzsh_flush(qp->tzsh);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_scrollable_get(tzsh_quickpanel_h qp,
                               tzsh_quickpanel_scrollable_state_e *scroll)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   /* TODO */

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_orientation_get(tzsh_quickpanel_h qp,
                                tzsh_quickpanel_orientation_state_e *ori)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   /* TODO */

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_state_change_cb_set(tzsh_quickpanel_h qp,
                                    tzsh_quickpanel_cb cb_func,
                                    void *data)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   /* TODO */

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_state_change_cb_unset(tzsh_quickpanel_h qp)
{
   if (!qp)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);

   /* TODO */

   TZSH_ERR_SUCCESS_RET;
}
