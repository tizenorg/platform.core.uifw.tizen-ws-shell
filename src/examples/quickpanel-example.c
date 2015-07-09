#include <Elementary.h>

#include <efl_extension.h>
#include <tzsh_quickpanel.h>
#include <tzsh_quickpanel_service.h>


#define WIDTH  100
#define HEIGHT 100

static Evas_Object *
_create_and_show_window(const char *name)
{
   Evas_Object *win, *bg;

   win = elm_win_util_standard_add(name , name);
   elm_win_autodel_set(win, EINA_TRUE);

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
   tzsh_quickpanel_service_h qp_service;
   tzsh_region_h region;
   tzsh_native_window win_id = 0;

   win = _create_and_show_window("Tzsh Service Examples");

   win_id = eext_win_tzsh_native_window_get(win);
   if (!win_id)
     {
        fprintf(stderr, "Failed to get window ID\n");
        return;
     }

   qp_service = tzsh_quickpanel_service_create(tzsh, win_id);

   region = tzsh_region_create(tzsh);
   tzsh_region_add(region, 0, 0, 720, 100);
   tzsh_quickpanel_service_content_region_set(qp_service, 0, region);
   tzsh_quickpanel_service_handler_region_set(qp_service, 0, region);
   tzsh_region_destroy(region);
}

static void
user_win_test(tzsh_h tzsh)
{
   Evas_Object *win;
   tzsh_quickpanel_h qp;
   tzsh_native_window win_id = 0;

   win = _create_and_show_window("Tzsh User Examples");

   win_id = eext_win_tzsh_native_window_get(win);
    if (!win_id)
     {
        fprintf(stderr, "Failed to get window ID\n");
        return;
     }

   qp = tzsh_quickpanel_create(tzsh, win_id);
   tzsh_quickpanel_show(qp);
   tzsh_quickpanel_hide(qp);
   tzsh_quickpanel_enable(qp);
   tzsh_quickpanel_disable(qp);

   tzsh_quickpanel_destroy(qp);
}

EAPI_MAIN int
elm_main(int argc EINA_UNUSED, char *argv[] EINA_UNUSED)
{
   tzsh_h tzsh;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
   if (!tzsh)
     {
        fprintf(stderr, "Failed to init tzsh\n");
        return -1;
     }

   service_win_test(tzsh);
   user_win_test(tzsh);

   elm_run();

   tzsh_destroy(tzsh);

   return 0;
}
ELM_MAIN()
