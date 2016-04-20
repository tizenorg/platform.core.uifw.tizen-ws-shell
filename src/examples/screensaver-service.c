#include <Elementary.h>
#include <tzsh_screensaver_service.h>

EAPI_MAIN int
elm_main(int argc EINA_UNUSED, char *argv[] EINA_UNUSED)
{
   tzsh_h tzsh = NULL;
   tzsh_window tz_win = NULL;
   tzsh_screensaver_service_h tz_scrsaver = NULL;
   Evas_Object *win = NULL, *bg = NULL;
   const char *name = "Tzsh Screensaver Service Example";

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
   if (!tzsh)
     {
        fprintf(stderr, "Failed to init tzsh\n");
        return -1;
     }

   win = elm_win_util_standard_add(name , name);
   elm_win_autodel_set(win, EINA_TRUE);
   bg = elm_bg_add(win);
   evas_object_color_set(bg, 255, 0, 0, 255);
   elm_win_resize_object_add(win, bg);
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

   tz_scrsaver = tzsh_screensaver_service_create(tzsh, tz_win);

   elm_run();

   tzsh_screensaver_service_destroy(tz_scrsaver);
   tzsh_destroy(tzsh);

   return 0;
}
ELM_MAIN()
