#include <assert.h>
#include <stdio.h>

#include <tzsh.h>

#include "test-runner.h"

TEST(test_tzsh_create)
{
   tzsh_h tzsh;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
   assert(tzsh && "Failed to create tzsh");
   tzsh_destroy(tzsh);

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
   assert(tzsh && "Failed to create tzsh");
   tzsh_destroy(tzsh);

   // fail test
   tzsh = tzsh_create(3);
   assert(!tzsh && "tzsh should be not created");
}
