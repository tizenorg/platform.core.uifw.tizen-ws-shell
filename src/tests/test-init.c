#include "config.h"

#include <assert.h>
#include <stdio.h>

#include <tzsh.h>

#include "test-runner.h"

TEST(test_tzsh_create_type_unknown)
{
   tzsh_h tzsh;

   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_UNKNOWN);
   assert(tzsh && "Failed to create tzsh");
   tzsh_destroy(tzsh);
}

#ifdef HAVE_EFL
TEST(test_tzsh_create_type_efl)
{
   tzsh_h tzsh;

   DISABLE_LEAK_CHECKS  // disable alram for ecore_init().
   tzsh = tzsh_create(TZSH_TOOLKIT_TYPE_EFL);
   assert(tzsh && "Failed to create tzsh");
   tzsh_destroy(tzsh);
}
#endif

FAIL_TEST(tzsh_create_with_invaild_arg)
{
   tzsh_h tzsh;

   tzsh = tzsh_create(3);
   assert(tzsh && "tzsh should not be created"); // must fail
}
