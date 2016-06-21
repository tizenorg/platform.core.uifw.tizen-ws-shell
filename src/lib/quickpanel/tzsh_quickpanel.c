#include "tzsh_protect.h"
#include "tzsh_quickpanel.h"

TZSH_USER_BASE_DATA(quickpanel)
TZSH_USER_BASE_IMPL(quickpanel)

struct _tzsh_quickpanel_event_handler_s
{
   tzsh_quickpanel_event_type_e type;
   tzsh_quickpanel_event_cb func;
};

struct _tzsh_quickpanel_event_info_s
{
   tzsh_quickpanel_event_type_e type;
   int val;
};

struct tws_qp_event
{
   int type;
   int val;
};

struct tzsh_qp_cb
{
   tzsh_quickpanel_event_cb func;
   void *data;
};

struct private_data
{
   struct tzsh_qp_cb callbacks[4];

   struct
   {
      int type;
   } request;

   struct
   {
      int wait_for_done;
      int type;
      int val;
   } reply;
};

static void                 _cb_destroy(void *data);
static int                  _ev_check(int tws_type,
                                      int tws_val,
                                      int *tzsh_val);
static struct tzsh_qp_cb   *_cb_get(struct private_data *pd,
                                    int tws_type);
static struct private_data *_private_data_get(tzsh_quickpanel_h qp);
static int                  _event_val_get(tzsh_quickpanel_event_info_h event_info,
                                           int *state);
static int                  _state_get(tzsh_quickpanel_h qp,
                                       int tws_state_type,
                                       int *val);
static void                 _tws_qp_cb_state_get_done(void *data,
                                                      struct tws_quickpanel *tws_qp,
                                                      int tws_type,
                                                      int tws_val,
                                                      uint32_t error_state);
static void                 _tws_qp_cb_state_changed(void *data,
                                                     struct tws_quickpanel *tws_qp,
                                                     struct wl_array *states);

static const struct tws_quickpanel_listener _tws_qp_listener =
{
   _tws_qp_cb_state_get_done,
   _tws_qp_cb_state_changed
};

static void
_cb_destroy(void *data)
{
   tzsh_quickpanel_h qp = data;
   struct private_data *pd;

   if ((!qp) || (!qp->private_data))
     return;

   pd = qp->private_data;

   tws_quickpanel_destroy(qp->res);

   memset(pd, 0x0, sizeof(struct private_data));
   free(pd);
}

static int
_ev_check(int tws_type,
          int tws_val,
          int *tzsh_val)
{
   int res = -1;

   switch (tws_type)
     {
      case TWS_QUICKPANEL_STATE_TYPE_VISIBILITY:
         if      (tws_val == TWS_QUICKPANEL_STATE_VALUE_VISIBLE_SHOW) { *tzsh_val = TZSH_QUICKPANEL_STATE_VISIBLE_SHOW; res = 1; }
         else if (tws_val == TWS_QUICKPANEL_STATE_VALUE_VISIBLE_HIDE) { *tzsh_val = TZSH_QUICKPANEL_STATE_VISIBLE_HIDE; res = 1; }
         break;
      case TWS_QUICKPANEL_STATE_TYPE_SCROLLABLE:
         if      (tws_val == TWS_QUICKPANEL_STATE_VALUE_SCROLLABLE_SET  ) { *tzsh_val = TZSH_QUICKPANEL_STATE_SCROLLABLE_SET;   res = 1; }
         else if (tws_val == TWS_QUICKPANEL_STATE_VALUE_SCROLLABLE_UNSET) { *tzsh_val = TZSH_QUICKPANEL_STATE_SCROLLABLE_UNSET; res = 1; }
         break;
      case TWS_QUICKPANEL_STATE_TYPE_ORIENTATION:
         if      (tws_val == TWS_QUICKPANEL_STATE_VALUE_ORIENTATION_0  ) { *tzsh_val = TZSH_QUICKPANEL_STATE_ORIENTATION_0;   res = 1; }
         else if (tws_val == TWS_QUICKPANEL_STATE_VALUE_ORIENTATION_90 ) { *tzsh_val = TZSH_QUICKPANEL_STATE_ORIENTATION_90;  res = 1; }
         else if (tws_val == TWS_QUICKPANEL_STATE_VALUE_ORIENTATION_180) { *tzsh_val = TZSH_QUICKPANEL_STATE_ORIENTATION_180; res = 1; }
         else if (tws_val == TWS_QUICKPANEL_STATE_VALUE_ORIENTATION_270) { *tzsh_val = TZSH_QUICKPANEL_STATE_ORIENTATION_270; res = 1; }
         break;
      default:
         break;
     }

   return res;
}

static struct tzsh_qp_cb *
_cb_get(struct private_data *pd,
        int tws_type)
{
   struct tzsh_qp_cb *cb = NULL;
   int idx = -1;

   switch (tws_type)
     {
      case TWS_QUICKPANEL_STATE_TYPE_VISIBILITY:  idx = 1; break;
      case TWS_QUICKPANEL_STATE_TYPE_SCROLLABLE:  idx = 2; break;
      case TWS_QUICKPANEL_STATE_TYPE_ORIENTATION: idx = 3; break;
      default: break;
     }

   if (idx != -1)
     {
        if (pd->callbacks[idx].func)
          cb = &pd->callbacks[idx];
     }

   return cb;
}

static struct private_data *
_private_data_get(tzsh_quickpanel_h qp)
{
   struct private_data *pd = qp->private_data;

   if (!pd)
     {
        pd = calloc(1, sizeof(struct private_data));
        if (!pd) return NULL;

        tzsh_destroy_callback_add(qp->tzsh, _cb_destroy, qp);
        tws_quickpanel_set_user_data(qp->res, qp);
        qp->private_data = pd;

        tws_quickpanel_add_listener(qp->res, &_tws_qp_listener, qp);
     }

   return pd;
}

static int
_event_val_get(tzsh_quickpanel_event_info_h event_info,
               int *state)
{
   if ((!event_info) || (!state))
     {
        TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
     }

   *state = event_info->val;

   TZSH_ERR_SUCCESS_RET;
}

static int
_state_get(tzsh_quickpanel_h qp,
           int tws_state_type,
           int *val)
{
   struct private_data *pd;
   int cnt = 0;

   if ((!qp) || (!val))
     {
        TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
     }

   pd = _private_data_get(qp);
   if (!pd) TZSH_ERR_RET(TZSH_ERROR_OUT_OF_MEMORY);

   pd->request.type = tws_state_type;
   pd->reply.wait_for_done = 1;
   pd->reply.type = TWS_QUICKPANEL_STATE_TYPE_UNKNOWN;
   pd->reply.val = -1;

   tws_quickpanel_state_get(qp->res, tws_state_type);
   while ((pd->reply.wait_for_done) && (cnt < 10))
     {
        tzsh_flush(qp->tzsh);
        tzsh_dispatch(qp->tzsh);
        cnt++;
     }

   if (pd->reply.wait_for_done)
     {
        pd->reply.wait_for_done = 0;
        pd->reply.type = TWS_QUICKPANEL_STATE_TYPE_UNKNOWN;
        pd->reply.val = -1;
        TZSH_ERR_RET(TZSH_ERROR_PERMISSION_DENIED);
     }

   if (val) *val = pd->reply.val;

   pd->reply.wait_for_done = 0;
   pd->reply.type = TWS_QUICKPANEL_STATE_TYPE_UNKNOWN;
   pd->reply.val = -1;

   TZSH_ERR_SUCCESS_RET;
}

static void
_tws_qp_cb_state_get_done(void *data,
                          struct tws_quickpanel *tws_qp,
                          int tws_type,
                          int tws_val,
                          uint32_t error_state)
{
   tzsh_quickpanel_h qp = data;
   struct private_data *pd;
   struct tzsh_qp_cb *cb;
   int res, tzsh_state_val;

   if ((!qp) || (!qp->private_data))
     return;

   pd = qp->private_data;

   /* check validation for tws event type and value
    * and get tzsh_state_value from tws_val
    */
   res = _ev_check(tws_type, tws_val, &tzsh_state_val);
   if (res == -1) return;

   /* get callback structure from private data */
   cb = _cb_get(pd, tws_type);
   if (!cb) return;

   if (pd->request.type == tws_type)
     {
        pd->reply.wait_for_done = 0;
        pd->reply.val = tzsh_state_val;
     }
}

static void
_tws_qp_cb_state_changed(void *data,
                         struct tws_quickpanel *tws_qp,
                         struct wl_array *states)
{
   tzsh_quickpanel_h qp = data;
   struct private_data *pd;
   struct tzsh_qp_cb *cb;
   tzsh_quickpanel_event_info_h ev;
   int res, tzsh_state_val;
   struct tws_qp_event *tws_ev;

   if ((!qp) || (!qp->private_data))
     return;

   pd = qp->private_data;

   wl_array_for_each(tws_ev, states)
     {
        /* check validation for tws event type and value
         * and get tzsh_state_value from tws value
         */
        res = _ev_check(tws_ev->type,
                        tws_ev->val,
                        &tzsh_state_val);
        if (res == -1) continue;

        /* get callback structure from private data */
        cb = _cb_get(pd, tws_ev->type);
        if (cb)
          {
             ev = calloc(1, sizeof(struct _tzsh_quickpanel_event_info_s));
             ev->type = tws_ev->type;
             ev->val = tzsh_state_val;

             /* call user registred callback handler */
             cb->func(ev, cb->data);

			 memset(ev, 0x0, sizeof(struct _tzsh_quickpanel_event_info_s));
             free(ev);
          }
     }
}

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
                            tzsh_quickpanel_state_visible_e *vis)
{
   return _state_get(qp, TWS_QUICKPANEL_STATE_TYPE_VISIBILITY, (int *)vis);
}

TZSH_EXPORT int
tzsh_quickpanel_event_handler_add(tzsh_quickpanel_h qp,
                                  tzsh_quickpanel_event_handler_h *event_handler,
                                  tzsh_quickpanel_event_type_e event_type,
                                  tzsh_quickpanel_event_cb callback,
                                  void *data)
{
   tzsh_quickpanel_event_handler_h handler;
   struct private_data *pd;
   int idx = -1;

   if ((!qp) ||
       (!qp->private_data) ||
       (!event_handler) ||
       (event_type < TZSH_QUICKPANEL_EVENT_TYPE_VISIBILITY) ||
       (event_type > TZSH_QUICKPANEL_EVENT_TYPE_ORIENTATION) ||
       (!callback))
     {
        TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
     }

   switch (event_type)
     {
      case TZSH_QUICKPANEL_EVENT_TYPE_VISIBILITY:  idx = 1; break;
      case TZSH_QUICKPANEL_EVENT_TYPE_SCROLLABLE:  idx = 1; break;
      case TZSH_QUICKPANEL_EVENT_TYPE_ORIENTATION: idx = 1; break;
      default:
         TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
         break;
     }

   pd = qp->private_data;
   pd->callbacks[idx].func = callback;
   pd->callbacks[idx].data = data;

   handler = calloc(1, sizeof(struct _tzsh_quickpanel_event_handler_s));
   handler->type = event_type;
   handler->func = callback;

   *event_handler = handler;

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_event_handler_del(tzsh_quickpanel_h qp,
                                  tzsh_quickpanel_event_handler_h event_handler)
{
   struct private_data *pd;
   int idx = -1;

   if ((!qp) ||
       (!qp->private_data) ||
       (!event_handler))
     {
        TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
     }

   switch (event_handler->type)
     {
      case TWS_QUICKPANEL_STATE_TYPE_VISIBILITY:  idx = 1; break;
      case TWS_QUICKPANEL_STATE_TYPE_SCROLLABLE:  idx = 2; break;
      case TWS_QUICKPANEL_STATE_TYPE_ORIENTATION: idx = 3; break;
      default:
         TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
         break;
     }

   pd = qp->private_data;
   if (pd->callbacks[idx].func == event_handler->func)
     {
        pd->callbacks[idx].func = NULL;
        pd->callbacks[idx].data = NULL;
     }

   memset(event_handler, 0x0, sizeof(struct _tzsh_quickpanel_event_handler_s));
   free(event_handler);

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_event_type_get(tzsh_quickpanel_event_info_h event_info,
                               tzsh_quickpanel_event_type_e *event_type)
{
   if ((!event_info) || (!event_type))
     {
        TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
     }

   *event_type = event_info->type;

   TZSH_ERR_SUCCESS_RET;
}

TZSH_EXPORT int
tzsh_quickpanel_event_scrollable_get(tzsh_quickpanel_event_info_h event_info,
                                     tzsh_quickpanel_state_scrollable_e *state)
{
   return _event_val_get(event_info, (int *)state);
}

TZSH_EXPORT int
tzsh_quickpanel_event_visible_get(tzsh_quickpanel_event_info_h event_info,
                                  tzsh_quickpanel_state_visible_e *state)
{
   return _event_val_get(event_info, (int *)state);
}

TZSH_EXPORT int
tzsh_quickpanel_event_orientation_get(tzsh_quickpanel_event_info_h event_info,
                                      tzsh_quickpanel_state_orientation_e *state)
{
   return _event_val_get(event_info, (int *)state);
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
                               tzsh_quickpanel_state_scrollable_e *scroll)
{
   return _state_get(qp, TWS_QUICKPANEL_STATE_TYPE_SCROLLABLE, (int *)scroll);
}

TZSH_EXPORT int
tzsh_quickpanel_orientation_get(tzsh_quickpanel_h qp,
                                tzsh_quickpanel_state_orientation_e *ori)
{
   return _state_get(qp, TWS_QUICKPANEL_STATE_TYPE_ORIENTATION, (int *)ori);
}
