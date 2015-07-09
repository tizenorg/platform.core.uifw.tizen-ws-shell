#include <assert.h>
#include <stdio.h>

#include <tzsh_call_service.h>
#include <tzsh_volume_service.h>
#include <tzsh_lockscreen_service.h>
#include <tzsh_quickpanel_service.h>
#include <tzsh_indicator_service.h>

#include "test-runner.h"

#define SERVICE_CREATE(obj, name, pobj, id)        \
   obj = tzsh_##name##_service_create(pobj, id);   \
   if (!obj)                                       \
      assert(0 && "Failed to create obj: "#name)

#define SERVICE_DESTROY(name, obj) tzsh_##name##_service_destroy(obj)

TEST(service_create_test)
{
   tzsh_h tzsh;
   tzsh_quickpanel_service_h qp;
   tzsh_lockscreen_service_h ls;
   tzsh_volume_service_h vm;
   tzsh_call_service_h cl;
   tzsh_indicator_service_h ind;
   tzsh_window win = 0x1234;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
   assert(tzsh && "Failed to create tzsh");

   SERVICE_CREATE(qp, quickpanel, tzsh, win);
   SERVICE_CREATE(ls, lockscreen, tzsh, win);
   SERVICE_CREATE(vm, volume, tzsh, win);
   SERVICE_CREATE(cl, call, tzsh, win);
   SERVICE_CREATE(ind, indicator, tzsh, win);

   SERVICE_DESTROY(quickpanel, qp);
   SERVICE_DESTROY(lockscreen, ls);
   SERVICE_DESTROY(volume, vm);
   SERVICE_DESTROY(call, cl);
   SERVICE_DESTROY(indicator, ind);

   tzsh_destroy(tzsh);
}

TEST(quickpanel_service_test)
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

   SERVICE_DESTROY(quickpanel, qp);

   tzsh_destroy(tzsh);

}

TEST(volume_service_test)
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
