AUTOMAKE_OPTIONS = 1.4 foreign

MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES =

AM_CPPFLAGS = \
-I./common \
-I./call \
-I./volume \
-I./lockscreen \
-I./quickpanel \
-I./indicator \
-I./tvsrv \
@WAYLAND_CFLAGS@ \
@TIZEN_COMMON_CFLAGS@

lib_LTLIBRARIES += common/libtzsh_common.la

common_libtzsh_common_la_SOURCES = \
      common/tzsh.c \
      common/tzsh_region.c \
      common/tzsh_service.c
common_libtzsh_common_la_LDFLAGS = -export-dynamic
common_libtzsh_common_la_CFLAGS = $(AM_CPPFLAGS)
common_libtzsh_common_la_LIBADD = @WAYLAND_LIBS@ @TIZEN_COMMON_LIBS@
if HAVE_EFL
common_libtzsh_common_la_SOURCES += common/tzsh_efl.c
common_libtzsh_common_la_CFLAGS += $(EFL_CFLAGS)
common_libtzsh_common_la_LIBADD += $(EFL_LIBS)
endif

commonlibtzshcommonincludedir = $(includedir)/tzsh
commonlibtzshcommoninclude_HEADERS = \
      common/tzsh.h \
      common/tzsh_region.h

nodist_common_libtzsh_common_la_SOURCES = \
      common/tzsh_private.h \
      common/tzsh_protocol.c \
      common/tzsh_protocol.h

lib_LTLIBRARIES += common/libtzsh_server.la
commonlibtzshserverincludedir = $(includedir)/tzsh
commonlibtzshserverinclude_HEADERS = \
      common/tzsh_server_core.h \
      common/tzsh_server.h

common_libtzsh_server_la_SOURCES = common/tzsh_protocol.c
common_libtzsh_server_la_CFLAGS = @WAYLAND_SERVER_CFLAGS@
common_libtzsh_server_la_LIBADD = @WAYLAND_SERVER_LIBS@

BUILT_SOURCES = \
      common/tzsh_protocol.c \
      common/tzsh_protocol.h \
      common/tzsh_server.h

CLEANFILES = $(BUILT_SOURCES)

common/%_protocol.c : $(top_srcdir)/protocol/%.xml
	$(AM_V_GEN)$(MKDIR_P) $(dir $@) && $(wayland_scanner) code < $< > $@
common/%_protocol.h : $(top_srcdir)/protocol/%.xml
	$(AM_V_GEN)$(MKDIR_P) $(dir $@) && $(wayland_scanner) client-header < $< > $@
common/%_server_core.h : $(top_srcdir)/protocol/%.xml
	$(AM_V_GEN)$(MKDIR_P) $(dir $@) && $(wayland_scanner) server-header < $< > $@

include Makefile_Call.am
include Makefile_Volume.am
include Makefile_Lockscreen.am
include Makefile_Quickpanel.am
include Makefile_Indicator.am
include Makefile_Tvsrv.am
