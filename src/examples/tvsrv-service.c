#include <Elementary.h>
#include <tzsh_tvsrv_service.h>

#define WIDTH  100
#define HEIGHT 100

static Evas_Object *
_create_and_show_window(const char *name, Eina_Bool alpha)
{
   Evas_Object *win, *bg;

   win = elm_win_util_standard_add(name , name);
   elm_win_autodel_set(win, EINA_TRUE);
   if (alpha)
     elm_win_alpha_set(win, EINA_TRUE);

   bg = elm_bg_add(win);
   evas_object_color_set(bg, 255, 0, 0, 255);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   evas_object_resize(win, WIDTH, HEIGHT);
   evas_object_show(win);

   return win;
}

static void
service_win_test(tzsh_h tzsh)
{
   Evas_Object *win;
   tzsh_tvsrv_service_h tvsrv_service;
   tzsh_window tz_win;

   win = _create_and_show_window("Tzsh Service Examples", EINA_TRUE);
   tz_win = elm_win_window_id_get(win);
   if (!tz_win)
     {
        fprintf(stderr, "Failed to get window ID\n");
        return;
     }

   tvsrv_service = tzsh_tvsrv_service_create(tzsh, tz_win);
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

   service_win_test(tzsh);

   elm_run();

   tzsh_destroy(tzsh);

   return 0;
}
ELM_MAIN()
