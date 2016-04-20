ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = \
   -I$(top_srcdir)/src/lib/common \
   -I$(top_srcdir)/src/lib/quickpanel/ \
   -I$(top_srcdir)/src/lib/lockscreen/ \
   -I$(top_srcdir)/src/lib/volume/ \
   -I$(top_srcdir)/src/lib/call/ \
   -I$(top_srcdir)/src/lib/srv/ \
   -I$(top_builddir)/src/lib/ \
   -I$(top_builddir)/src/lib/quickpanel/ \
   -I$(top_builddir)/src/lib/lockscreen/ \
   -I$(top_builddir)/src/lib/volume/ \
   -I$(top_builddir)/src/lib/call/ \
   -I$(top_builddir)/src/lib/tvsrv/ \
   -I$(top_builddir)/src/lib/screensaver/ \
   @ELEMENTARY_CFLAGS@

bin_PROGRAMS = \
quickpanel-service \
quickpanel-client \
tvsrv-service \
tvsrv-client \
screensaver-manager-service \
screensaver-service

quickpanel_service_SOURCES = quickpanel-service.c
quickpanel_service_CFLAGS = $(AM_CFALGS)
quickpanel_service_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/quickpanel/libtzsh_quickpanel_service.la \
   @ELEMENTARY_LIBS@

quickpanel_client_SOURCES = quickpanel-client.c
quickpanel_client_CFLAGS = $(AM_CFALGS)
quickpanel_client_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/quickpanel/libtzsh_quickpanel.la \
   @ELEMENTARY_LIBS@

tvsrv_service_SOURCES = tvsrv-service.c
tvsrv_service_CFLAGS = $(AM_CFALGS)
tvsrv_service_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/tvsrv/libtzsh_tvsrv_service.la \
   @ELEMENTARY_LIBS@

tvsrv_client_SOURCES = tvsrv-client.c
tvsrv_client_CFLAGS = $(AM_CFALGS)
tvsrv_client_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/tvsrv/libtzsh_tvsrv.la \
   @ELEMENTARY_LIBS@

screensaver_manager_service_SOURCES = screensaver-manager-service.c
screensaver_manager_service_CFLAGS = $(AM_CFALGS)
screensaver_manager_service_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/screensaver/libtzsh_screensaver_manager_service.la \
   @ELEMENTARY_LIBS@

screensaver_service_SOURCES = screensaver-service.c
screensaver_service_CFLAGS = $(AM_CFALGS)
screensaver_service_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/screensaver/libtzsh_screensaver_service.la \
   @ELEMENTARY_LIBS@
