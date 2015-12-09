ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = \
   -I$(top_srcdir)/src/lib/common/ \
   -I$(top_srcdir)/src/lib/quickpanel/ \
   -I$(top_srcdir)/src/lib/lockscreen/ \
   -I$(top_srcdir)/src/lib/volume/ \
   -I$(top_srcdir)/src/lib/call/ \
   -I$(top_srcdir)/src/lib/indicator \
   -I$(top_srcdir)/src/lib/tvsrv \
   -I$(top_builddir)/src/lib/ \
   -I$(top_builddir)/src/lib/quickpanel/ \
   -I$(top_builddir)/src/lib/lockscreen/ \
   -I$(top_builddir)/src/lib/volume/ \
   -I$(top_builddir)/src/lib/call/ \
   -I$(top_builddir)/src/lib/indicator \
   -I$(top_builddir)/src/lib/tvsrv \
   @DAEMON_CFLAGS@

TESTS = \
   test-init \
   test-region \
   test-service \
   test-client

check_PROGRAMS = $(TESTS)

check_LTLIBRARIES = libtest-runner.la
libtest_runner_la_SOURCES =      \
      test-runner.c              \
      test-runner.h              \
      test-helpers.c             \
      test-daemon.c              \
      tzsh-protocol.c
libtest_runner_la_CFLAGS = $(AM_CPPFLAGS)
libtest_runner_la_LIBADD = @DAEMON_LIBS@ -lrt -ldl

TEST_COMMON_LDADD = \
libtest-runner.la \
$(top_builddir)/src/lib/common/libtzsh_common.la

TEST_SERVICE_LDADD = \
$(top_builddir)/src/lib/call/libtzsh_call_service.la \
$(top_builddir)/src/lib/volume/libtzsh_volume_service.la \
$(top_builddir)/src/lib/lockscreen/libtzsh_lockscreen_service.la \
$(top_builddir)/src/lib/quickpanel/libtzsh_quickpanel_service.la \
$(top_builddir)/src/lib/indicator/libtzsh_indicator_service.la \
$(top_builddir)/src/lib/tvsrv/libtzsh_tvsrv_service.la

TEST_SHELL_LDADD = $(top_builddir)/src/lib/quickpanel/libtzsh_quickpanel.la

test_init_SOURCES = test-init.c
test_init_LDADD = $(TEST_COMMON_LDADD)

test_region_SOURCES = test-region.c
test_region_LDADD = $(TEST_COMMON_LDADD)

test_service_SOURCES = test-service.c
test_service_LDADD = \
$(TEST_COMMON_LDADD) \
$(TEST_SERVICE_LDADD)
if HAVE_ECORE
test_service_CFLAGS = @ECORE_CFLAGS@
test_service_LDADD += @ECORE_LIBS@
endif

test_client_SOURCES = test-client.c
test_client_LDADD = \
$(TEST_COMMON_LDADD) \
$(TEST_SHELL_LDADD)

BUILT_SOURCES = \
      tzsh-protocol.c \
      tzsh-protocol.h

CLEANFILES = $(BUILT_SOURCES)

%-protocol.c : $(top_srcdir)/protocol/%.xml
	$(AM_V_GEN)$(MKDIR_P) $(dir $@) && $(wayland_scanner) code < $< > $@

%-protocol.h : $(top_srcdir)/protocol/%.xml
	$(AM_V_GEN)$(MKDIR_P) $(dir $@) && $(wayland_scanner) server-header < $< > $@
