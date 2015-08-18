#include "config.h"

#include <assert.h>
#include <stdio.h>

#ifdef HAVE_EFL
#include <Ecore.h>
#endif

#include <tzsh_call_service.h>
#include <tzsh_volume_service.h>
#include <tzsh_lockscreen_service.h>
#include <tzsh_quickpanel_service.h>
#include <tzsh_indicator_service.h>
#include <tzsh_tvsrv_service.h>

#include "test-runner.h"

#define SERVICE_CREATE(obj, name, pobj, id)        \
   obj = tzsh_##name##_service_create(pobj, id);   \
   if (!obj)                                       \
      assert(0 && "Failed to create obj: "#name)

#define SERVICE_CREATE_FAIL(obj, name, pobj, id)   \
   obj = tzsh_##name##_service_create(NULL, id);   \
   assert(!obj && "must fail to create object");   \
   obj = tzsh_##name##_service_create(pobj, 0);    \
   assert(!obj && "must fail to create object");   \
   obj = tzsh_##name##_service_create(NULL, 0);    \
   assert(!obj && "must fail to create object");

#define SERVICE_DESTROY(name, obj) tzsh_##name##_service_destroy(obj)

static tzsh_h
setup(void)
{
   tzsh_h tzsh;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
   assert(tzsh && "failed to create tzsh");

   return tzsh;
}

static void
cleanup(tzsh_h tzsh)
{
   tzsh_destroy(tzsh);
}

TEST(test_service_create)
{
   tzsh_h tzsh;
   tzsh_quickpanel_service_h qp;
   tzsh_lockscreen_service_h ls;
   tzsh_volume_service_h vm;
   tzsh_call_service_h cl;
   tzsh_indicator_service_h ind;
   tzsh_tvsrv_service_h ts;
   tzsh_window win = 0x1234;

   tzsh = setup();

   SERVICE_CREATE(qp, quickpanel, tzsh, win);
   SERVICE_CREATE(ls, lockscreen, tzsh, win);
   SERVICE_CREATE(vm, volume, tzsh, win);
   SERVICE_CREATE(cl, call, tzsh, win);
   SERVICE_CREATE(ind, indicator, tzsh, win);
   SERVICE_CREATE(ts, tvsrv, tzsh, win);

   SERVICE_DESTROY(quickpanel, qp);
   SERVICE_DESTROY(lockscreen, ls);
   SERVICE_DESTROY(volume, vm);
   SERVICE_DESTROY(call, cl);
   SERVICE_DESTROY(indicator, ind);
   SERVICE_DESTROY(tvsrv, ts);

   cleanup(tzsh);
}

TEST(fail_test_service_create_with_invalid_arg)
{
   tzsh_h tzsh;
   tzsh_quickpanel_service_h qp;
   tzsh_lockscreen_service_h ls;
   tzsh_volume_service_h vm;
   tzsh_call_service_h cl;
   tzsh_indicator_service_h ind;
   tzsh_window win = 0x1234;

   tzsh = setup();

   SERVICE_CREATE_FAIL(qp, quickpanel, tzsh, win);
   SERVICE_CREATE_FAIL(ls, lockscreen, tzsh, win);
   SERVICE_CREATE_FAIL(vm, volume, tzsh, win);
   SERVICE_CREATE_FAIL(cl, call, tzsh, win);
   SERVICE_CREATE_FAIL(ind, indicator, tzsh, win);

   cleanup(tzsh);
}

TEST(test_quickpanel_service)
{
   tzsh_h tzsh;
   tzsh_quickpanel_service_h qp;
   tzsh_region_h region;
   tzsh_window win = 0x1234;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
   assert(tzsh && "Failed to create tzsh");

   SERVICE_CREATE(qp, quickpanel, tzsh, win);

   region = tzsh_region_create(tzsh);
   tzsh_region_add(region, 200, 200, 200, 200);
   tzsh_quickpanel_service_content_region_set(qp, 0, region);
   tzsh_region_destroy(region);

   region = tzsh_region_create(tzsh);
   tzsh_region_add(region, 200, 200, 200, 200);
   tzsh_region_subtract(region, 0, 0, 200, 100);
   tzsh_quickpanel_service_handler_region_set(qp, 0, region);
   tzsh_region_destroy(region);

   tzsh_quickpanel_service_show(qp);
   tzsh_quickpanel_service_hide(qp);

   SERVICE_DESTROY(quickpanel, qp);

   tzsh_destroy(tzsh);
}

TEST(test_volume_service)
{
   tzsh_h tzsh;
   tzsh_volume_service_h vm;
   tzsh_region_h region;
   tzsh_window win = 0x1234;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
   assert(tzsh && "Failed to create tzsh");

   SERVICE_CREATE(vm, volume, tzsh, win);

   region = tzsh_region_create(tzsh);
   tzsh_region_add(region, 200, 200, 200, 200);
   tzsh_volume_service_content_region_set(vm, 0, region);
   tzsh_region_destroy(region);

   SERVICE_DESTROY(volume, vm);

   tzsh_destroy(tzsh);
}

#ifdef HAVE_EFL
static void
cb_indicator_service(void *data, tzsh_indicator_service_h service, int angle, int opacity)
{
   int *flag = data;

   if ((angle == 90) && (opacity == 1))
     *flag = 1;
   ecore_main_loop_quit();
}

static Eina_Bool
cb_timeout(void *data)
{
   ecore_main_loop_quit();

   return ECORE_CALLBACK_DONE;
}

TEST(test_indicator_service)
{
   tzsh_h tzsh;
   tzsh_indicator_service_h ind;
   tzsh_window win = 0x1234;
   int res = 0;
   int flag = 0;
   Ecore_Timer *timeout;

   DISABLE_LEAK_CHECKS

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
   assert(tzsh && "Failed to create tzsh");

   SERVICE_CREATE(ind, indicator, tzsh, win);

   tzsh_indicator_service_property_change_cb_set(ind, cb_indicator_service, &flag);

   res = ecore_init();
   assert(res && "failed to init ecore");

   timeout = ecore_timer_add(3, cb_timeout, NULL);

   ecore_main_loop_begin();
   assert(flag && "'flag' must be set as 1");

   ecore_shutdown();

   SERVICE_DESTROY(indicator, ind);

   tzsh_destroy(tzsh);
}
#endif
