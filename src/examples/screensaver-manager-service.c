#include <Elementary.h>
#include <tzsh_screensaver_manager_service.h>

static pid_t child_pid = -1;
static Eina_Bool enable = EINA_FALSE;
static tzsh_screensaver_manager_service_h scrsavermng = NULL;

void
_cb_state_change(void *data, tzsh_screensaver_manager_service_h service, int states)
{
   char buff[1024];

   if (states & TZSH_SCREENSAVER_MANAGER_SERVICE_STATE_IDLE_TIMEOUT_EXPIRED)
     {
        fprintf(stdout, "current state: idle timeout expired\n");
        child_pid = fork();
        switch (child_pid)
          {
           case -1:
              fprintf(stdout, "fork failed.\n");
              break;
           case 0:
              execl("/usr/bin/screensaver-service", "screensaver-service", NULL);
              fprintf(stdout, "execl failed.\n");
              break;
           default:
              fprintf(stdout, "child pid:%d\n", child_pid);
              break;
          }
     }
   else if (states & TZSH_SCREENSAVER_MANAGER_SERVICE_STATE_NOT_IDLE)
     {
        fprintf(stdout, "current state: not idle\n");
        if (child_pid)
          {
             switch (fork())
               {
                case -1:
                   fprintf(stdout, "fork failed.\n");
                   break;
                case 0:
                   sprintf(buff, "%d", child_pid);
                   fprintf(stdout, "kill pid:%s\n", buff);
                   execl("/usr/bin/kill", "kill", "-9", buff, NULL);
                   fprintf(stdout, "execl failed.\n");
                   break;
                default:
                   fprintf(stdout, "success\n");
                   break;
               }
          }
     }
}

static void
_cb_bt_clicked(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   Evas_Object *lb = data;

   enable = !enable;
   if (enable)
     {
        tzsh_screensaver_manager_service_enable(scrsavermng);
        elm_object_text_set(lb, "Screensaver: Enable");
     }
   else
     {
        tzsh_screensaver_manager_service_disable(scrsavermng);
        elm_object_text_set(lb, "Screensaver: Disable");
     }

   fprintf(stdout, "Changed screensaver state: %s\n", enable ? "Enable" : "Disable");
}

EAPI_MAIN int
elm_main(int argc EINA_UNUSED, char *argv[] EINA_UNUSED)
{
   tzsh_h tzsh = NULL;
   tzsh_window tz_win = NULL;
   tzsh_screensaver_manager_service_h tz_scrsaver_mng = NULL;
   Evas_Object *win, *bg, *bx, *bt, *lb;
   const char *name = "Tzsh Screensaver Manager Service Example";

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
   if (!tzsh)
     {
        fprintf(stderr, "Failed to create and init tzsh\n");
        return -1;
     }

   win = elm_win_util_standard_add(name, name);
   elm_win_autodel_set(win, EINA_TRUE);
   bg = elm_bg_add(win);
   evas_object_color_set(bg, 120, 120, 200, 255);
   elm_win_resize_object_add(win, bg);

   bx = elm_box_add(win);

   lb = elm_label_add(win);
   elm_object_text_set(lb, "Screensaver: Enable");
   evas_object_size_hint_weight_set(lb, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(lb, EVAS_HINT_FILL, 0.0);
   elm_box_pack_end(bx, lb);
   evas_object_show(lb);

   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   bt = elm_button_add(win);
   elm_object_text_set(bt, "Screensaver");
   evas_object_smart_callback_add(bt, "clicked", _cb_bt_clicked, lb);
   elm_box_pack_end(bx, bt);
   evas_object_show(bt);

   evas_object_show(bx);
   evas_object_show(bg);
   evas_object_show(win);

   tz_win = elm_win_window_id_get(win);
   if (!tz_win)
     {
        fprintf(stderr, "Failed to get window ID\n");
        evas_object_del(win);
        tzsh_destroy(tzsh);
        return -1;
     }

   tz_scrsaver_mng = tzsh_screensaver_manager_service_create(tzsh, tz_win);
   tzsh_screensaver_manager_service_state_change_cb_set(tz_scrsaver_mng, _cb_state_change, NULL);
   tzsh_screensaver_manager_service_idle_timeout_set(tz_scrsaver_mng, 7000); /* 7000 milliseconds == 7 seconds */
   tzsh_screensaver_manager_service_enable(tz_scrsaver_mng);

   scrsavermng = tz_scrsaver_mng;
   enable = EINA_TRUE;

   elm_run();

   tzsh_screensaver_manager_service_destroy(tz_scrsaver_mng);
   tzsh_destroy(tzsh);

   return 0;
}
ELM_MAIN()
