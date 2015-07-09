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

bin_PROGRAMS = quickpanel-example

quickpanel_example_SOURCES = quickpanel-example.c
quickpanel_example_CFLAGS = $(AM_CFALGS)
quickpanel_example_LDADD = \
   $(top_builddir)/src/lib/common/libtzsh_common.la \
   $(top_builddir)/src/lib/quickpanel/libtzsh_quickpanel.la \
   $(top_builddir)/src/lib/quickpanel/libtzsh_quickpanel_service.la \
   @EFL_LIBS@
