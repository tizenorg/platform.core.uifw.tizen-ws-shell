ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = \
   -I$(top_srcdir)/src/lib/common \
   -I$(top_srcdir)/src/lib/quickpanel/ \
   -I$(top_srcdir)/src/lib/lockscreen/ \
   -I$(top_srcdir)/src/lib/volume/ \
   -I$(top_srcdir)/src/lib/call/ \
   -I$(top_builddir)/src/lib/ \
   -I$(top_builddir)/src/lib/quickpanel/ \
   -I$(top_builddir)/src/lib/lockscreen/ \
   -I$(top_builddir)/src/lib/volume/ \
   -I$(top_builddir)/src/lib/call/ \
   @EFL_CFLAGS@

bin_PROGRAMS = \
quickpanel-service \
quickpanel-client

quickpanel_service_SOURCES = quickpanel-service.c
quickpanel_service_CFLAGS = $(AM_CFALGS)
quickpanel_service_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/quickpanel/libtzsh_quickpanel_service.la \
   @EFL_LIBS@

quickpanel_client_SOURCES = quickpanel-client.c
quickpanel_client_CFLAGS = $(AM_CFALGS)
quickpanel_client_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/quickpanel/libtzsh_quickpanel.la \
   @EFL_LIBS@

