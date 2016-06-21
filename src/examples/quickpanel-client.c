#include <Elementary.h>
#include <tzsh_quickpanel.h>

#define WIDTH  100
#define HEIGHT 100

static tzsh_quickpanel_h qp = NULL;
static tzsh_quickpanel_event_handler_h handlers[3] = { NULL, NULL, NULL };

static void
_cb_visibility_changed(tzsh_quickpanel_event_info_h ev_info, void *data)
{
   tzsh_quickpanel_event_type_e ev_type;
   tzsh_quickpanel_state_visible_e state, curr;

   tzsh_quickpanel_event_type_get(ev_info, &ev_type);
   if (ev_type != TZSH_QUICKPANEL_EVENT_TYPE_VISIBILITY)
     {
        fprintf(stderr,
                "[QP] Error %s(%d) ev_type:%d\n",
                __func__, __LINE__, ev_type);
     }

   tzsh_quickpanel_event_visible_get(ev_info, &state);
   fprintf(stdout,
           "[QP] Callback %s(%d) state:%d\n",
           __func__, __LINE__, state);

   /* validation check */
   tzsh_quickpanel_visible_get(qp, &curr);
   fprintf(stdout,
           "[QP] Callback %s(%d) curr:%d\n",
           __func__, __LINE__, curr);

   tzsh_quickpanel_hide(qp);
   tzsh_quickpanel_visible_get(qp, &curr);
   fprintf(stdout,
           "[QP] Callback %s(%d) curr:%d\n",
           __func__, __LINE__, curr);

   tzsh_quickpanel_show(qp);
   tzsh_quickpanel_visible_get(qp, &curr);
   fprintf(stdout,
           "[QP] Callback %s(%d) curr:%d\n",
           __func__, __LINE__, curr);
}

static void
_cb_scrollable_changed(tzsh_quickpanel_event_info_h ev_info, void *data)
{
   tzsh_quickpanel_event_type_e ev_type;
   tzsh_quickpanel_state_scrollable_e state, curr;

   tzsh_quickpanel_event_type_get(ev_info, &ev_type);
   if (ev_type != TZSH_QUICKPANEL_EVENT_TYPE_SCROLLABLE)
     {
        fprintf(stderr,
                "[QP] Error %s(%d) ev_type:%d\n",
                __func__, __LINE__, ev_type);
     }

   tzsh_quickpanel_event_scrollable_get(ev_info, &state);
   fprintf(stdout,
           "[QP] Callback %s(%d) state:%d\n",
           __func__, __LINE__, state);

   /* validation check */
   tzsh_quickpanel_scrollable_get(qp, &curr);
   fprintf(stdout,
           "[QP] Callback %s(%d) curr:%d\n",
           __func__, __LINE__, curr);

   tzsh_quickpanel_scrollable_unset(qp);
   tzsh_quickpanel_scrollable_get(qp, &curr);
   fprintf(stdout,
           "[QP] Callback %s(%d) curr:%d\n",
           __func__, __LINE__, curr);

   tzsh_quickpanel_scrollable_set(qp);
   tzsh_quickpanel_scrollable_get(qp, &curr);
   fprintf(stdout,
           "[QP] Callback %s(%d) curr:%d\n",
           __func__, __LINE__, curr);
}

static void
_cb_orientation_changed(tzsh_quickpanel_event_info_h ev_info, void *data)
{
   tzsh_quickpanel_event_type_e ev_type;
   tzsh_quickpanel_state_orientation_e state, curr;

   tzsh_quickpanel_event_type_get(ev_info, &ev_type);
   if (ev_type != TZSH_QUICKPANEL_EVENT_TYPE_ORIENTATION)
     {
        fprintf(stderr,
                "[QP] Error %s(%d) ev_type:%d\n",
                __func__, __LINE__, ev_type);
     }

   tzsh_quickpanel_event_orientation_get(ev_info, &state);
   fprintf(stdout,
           "[QP] Callback %s(%d) state:%d\n",
           __func__, __LINE__, state);

   /* validation check */
   tzsh_quickpanel_orientation_get(qp, &curr);
   fprintf(stdout,
           "[QP] Callback %s(%d) curr:%d\n",
           __func__, __LINE__, curr);
}

static Evas_Object *
_create_and_show_window(const char *name, Eina_Bool alpha)
{
   Evas_Object *win, *bg;

   win = elm_win_util_standard_add(name , name);
   elm_win_autodel_set(win, EINA_TRUE);
   if (alpha)
     elm_win_alpha_set(win, EINA_TRUE);

   bg = elm_bg_add(win);
   evas_object_color_set(bg, 255, 255, 0, 255);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   evas_object_resize(win, WIDTH, HEIGHT);
   evas_object_show(win);

   return win;
}

static void
_init(tzsh_h tzsh)
{
   Evas_Object *win;
   tzsh_window tz_win;

   win = _create_and_show_window("Tzsh User Examples", EINA_FALSE);
   tz_win = elm_win_window_id_get(win);
   if (!tz_win)
     {
        fprintf(stderr, "Failed to get window ID\n");
        return;
     }

   qp = tzsh_quickpanel_create(tzsh, tz_win);

   tzsh_quickpanel_event_handler_add(qp, &handlers[0], TZSH_QUICKPANEL_EVENT_TYPE_VISIBILITY,  _cb_visibility_changed,  NULL);
   tzsh_quickpanel_event_handler_add(qp, &handlers[1], TZSH_QUICKPANEL_EVENT_TYPE_SCROLLABLE,  _cb_scrollable_changed,  NULL);
   tzsh_quickpanel_event_handler_add(qp, &handlers[2], TZSH_QUICKPANEL_EVENT_TYPE_ORIENTATION, _cb_orientation_changed, NULL);
}

static void
_deinit(void)
{
   tzsh_quickpanel_event_handler_del(qp, handlers[0]);
   tzsh_quickpanel_event_handler_del(qp, handlers[1]);
   tzsh_quickpanel_event_handler_del(qp, handlers[2]);

   tzsh_quickpanel_destroy(qp);
}

EAPI_MAIN int
elm_main(int argc EINA_UNUSED, char *argv[] EINA_UNUSED)
{
   tzsh_h tzsh;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
   if (!tzsh)
     {
        fprintf(stderr, "Failed to init tzsh\n");
        return -1;
     }

   _init(tzsh);

   elm_run();

   _deinit();

   tzsh_destroy(tzsh);

   return 0;
}
ELM_MAIN()
