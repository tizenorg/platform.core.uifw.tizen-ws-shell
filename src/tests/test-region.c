#include <assert.h>
#include <stdio.h>

#include <tzsh.h>
#include <tzsh_region.h>

#include "test-runner.h"

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

TEST(test_region_create)
{
   tzsh_h tzsh;
   tzsh_region_h region;

   tzsh = setup();

   region = tzsh_region_create(tzsh);
   assert(region && "failed to create region");
   tzsh_region_destroy(region);

   cleanup(tzsh);
}

FAIL_TEST(fail_test_region_create_with_invalid_arg)
{
   tzsh_region_h region;

   region = tzsh_region_create(NULL);
   assert(region && "must be NULL");   // must fail
}

TEST(test_region_add)
{
   tzsh_h tzsh;
   tzsh_region_h region;
   int ret;

   tzsh = setup();

   region = tzsh_region_create(tzsh);
   assert(region && "failed to create region");

   ret = tzsh_region_add(region, 0, 0, 123, 456);
   assert(!ret && "failed to add region");

   tzsh_region_destroy(region);

   cleanup(tzsh);
}

FAIL_TEST(fail_test_region_add_with_invalid_arg)
{
   tzsh_h tzsh;
   tzsh_region_h region;
   int ret;

   tzsh = setup();

   region = tzsh_region_create(tzsh);
   assert(region && "failed to create region");

   ret = tzsh_region_add(region, 0, 0, 0, 0);  // should be (w > 0) && (h > 0)
   assert(!ret && "failed to add region");   // must fail

   tzsh_region_destroy(region);

   cleanup(tzsh);
}

TEST(test_region_subtract)
{
   tzsh_h tzsh;
   tzsh_region_h region;
   int ret;

   tzsh = setup();

   region = tzsh_region_create(tzsh);
   assert(region && "failed to create region");

   ret = tzsh_region_subtract(region, 0, 0, 123, 456);
   assert(!ret && "failed to subtract region");

   tzsh_region_destroy(region);

   cleanup(tzsh);
}

FAIL_TEST(fail_test_region_subtract_with_invalid_arg)
{
   tzsh_h tzsh;
   tzsh_region_h region;
   int ret;

   tzsh = setup();

   region = tzsh_region_create(tzsh);
   assert(region && "failed to create region");

   ret = tzsh_region_subtract(region, 0, 0, 0, 0);  // should be (w > 0) && (h > 0)
   assert(!ret && "failed to add region");   // must fail

   tzsh_region_destroy(region);

   cleanup(tzsh);
}
