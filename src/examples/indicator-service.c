#include <Elementary.h>
#include <tzsh_indicator_service.h>

#define WIDTH  100
#define HEIGHT 100

static Evas_Object *
_create_and_show_window(const char *name, Eina_Bool alpha)
{
   Evas_Object *win;

   win = elm_win_add(NULL, name, ELM_WIN_SOCKET_IMAGE);
//   win = elm_win_util_standard_add(name , name);
   elm_win_autodel_set(win, EINA_TRUE);
   if (alpha)
     elm_win_alpha_set(win, EINA_TRUE);

   evas_object_resize(win, WIDTH, HEIGHT);
   evas_object_show(win);

   return win;
}

static void
_cb_property_change(void *data, tzsh_indicator_service_h service, int angle, int opacity)
{
	fprintf(stdout, "Change property... angle:%d, opacity:%d\n", angle, opacity);
	fprintf(stdout, "Change property... angle:%d, opacity:%d\n", angle, opacity);
	fprintf(stdout, "Change property... angle:%d, opacity:%d\n", angle, opacity);
	fprintf(stdout, "Change property... angle:%d, opacity:%d\n", angle, opacity);
	fprintf(stdout, "Change property... angle:%d, opacity:%d\n", angle, opacity);
}

static void
service_win_test(tzsh_h tzsh)
{
   Evas_Object *win;
   tzsh_indicator_service_h indi_service;
   tzsh_region_h region;
   tzsh_window tz_win;

   win = _create_and_show_window("Tzsh Indicator", EINA_TRUE);
   tz_win = elm_win_window_id_get(win);
   if (!tz_win)
     {
        fprintf(stderr, "Failed to get window ID\n");
//        return;
     }

   indi_service = tzsh_indicator_service_create(tzsh, tz_win);
   if (!indi_service)
     {
        fprintf(stderr, "Failed to create indi_service \n");
        return;
     }

   region = tzsh_region_create(tzsh);
   tzsh_region_add(region, 0, 0, 500, 50);
   tzsh_indicator_service_content_region_set(indi_service, 0, region);
   tzsh_region_destroy(region);

   tzsh_indicator_service_property_change_cb_set(indi_service, _cb_property_change, NULL);

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

