#include <assert.h>
#include <stdio.h>

#include <tzsh_quickpanel.h>

#include "test-runner.h"

#define SHELL_CREATE(pobj, obj, win, name)      \
   obj = tzsh_##name##_create(pobj, win);       \
   if (!obj)                                    \
      assert(0 && "Failed to get obj: "#name)

TEST(shell_get_test)
{
   tzsh_h tzsh;
   tzsh_quickpanel_h qp;
   tzsh_window win = 0x1234;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
   assert(tzsh && "Failed to create tzsh");

   SHELL_CREATE(tzsh, qp, win, quickpanel);

   tzsh_quickpanel_show(qp);
   tzsh_quickpanel_hide(qp);
   tzsh_quickpanel_enable(qp);
   tzsh_quickpanel_disable(qp);

   tzsh_quickpanel_destroy(qp);

   tzsh_destroy(tzsh);
}
