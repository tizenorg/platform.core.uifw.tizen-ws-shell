#include <assert.h>
#include <stdio.h>

#include <tzsh_quickpanel.h>

#include "test-runner.h"

#define SERVICE_HANDLE_CREATE(pobj, obj, win, name)      \
   obj = tzsh_##name##_create(pobj, win);       \
   if (!obj)                                    \
      assert(0 && "Failed to get obj: "#name)

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

TEST(test_service_handle_create)
{
   tzsh_h tzsh;
   tzsh_quickpanel_h qp;
   tzsh_window win = 0x1234;

   tzsh = setup();

   SERVICE_HANDLE_CREATE(tzsh, qp, win, quickpanel);

   tzsh_quickpanel_destroy(qp);

   cleanup(tzsh);
}

TEST(test_quickpanel_handling)
{
   tzsh_h tzsh;
   tzsh_quickpanel_h qp;
   tzsh_window win = 0x1234;
   int ret = 0;

   tzsh = setup();

   SERVICE_HANDLE_CREATE(tzsh, qp, win, quickpanel);

   ret = tzsh_quickpanel_show(qp);
   assert(!ret && "failed to request to show quickpanel");
   tzsh_quickpanel_hide(qp);
   assert(!ret && "failed to request to show quickpanel");
   tzsh_quickpanel_enable(qp);
   assert(!ret && "failed to request to show quickpanel");
   tzsh_quickpanel_disable(qp);
   assert(!ret && "failed to request to show quickpanel");

   tzsh_quickpanel_destroy(qp);

   cleanup(tzsh);
}
