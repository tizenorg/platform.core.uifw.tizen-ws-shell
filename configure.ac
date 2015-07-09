AC_INIT(Tzsh, [0.1.0], shiin.lee@samsung.com)
AC_CONFIG_SRCDIR(configure.ac)
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE(1.6 subdir-objects)

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

AC_PATH_PROG([wayland_scanner], [wayland-scanner])
if test x$wayland_scanner = x; then
      AC_MSG_ERROR([wayland-scanner is needed to compile Ecore-Buffer])
fi

PKG_CHECK_MODULES([WAYLAND], [wayland-client])
PKG_CHECK_MODULES([CAPI_BASE_COMMON], [capi-base-common])
PKG_CHECK_MODULES([DAEMON], [wayland-server])
PKG_CHECK_MODULES(WAYLAND_SCANNER, wayland-scanner)

PKG_CHECK_EXISTS([ecore-wayland],
                 [
                  AC_DEFINE([HAVE_ECORE_WAYLAND], [1], [ecore-wayland support for tzsh])
                  have_ecore_wayland="yes"
                  requirement_tzsh_pc="ecore-wayland"
                 ],
                 [have_ecore_wayland="no"])

AC_MSG_CHECKING([whether to build ecore-wayland backend])
AC_MSG_RESULT([${have_ecore_wayland}])

AC_ARG_ENABLE([build-examples],
   [AS_HELP_STRING([--enable-build-examples], [build examples. @<:@default=disabled@:>@])],
   [
    if test "x${enableval}" = "xyes" ; then
       want_build_examples="yes"
    else
       want_build_examples="no"
    fi
   ],
   [want_build_examples="no"])
AM_CONDITIONAL([BUILD_EXAMPLES], [test "${want_build_examples}" = "yes"])

if test "${want_build_examples}" = "yes"; then
   PKG_CHECK_MODULES([EFL], [evas elementary efl-extension])
fi

AC_CONFIG_FILES([
Makefile
pc/tzsh-common.pc
pc/tzsh-call.pc
pc/tzsh-call-service.pc
pc/tzsh-volume.pc
pc/tzsh-volume-service.pc
pc/tzsh-lockscreen.pc
pc/tzsh-lockscreen-service.pc
pc/tzsh-quickpanel.pc
pc/tzsh-quickpanel-service.pc
pc/tzsh-indicator.pc
pc/tzsh-indicator-service.pc
src/Makefile
src/lib/Makefile
src/examples/Makefile
src/tests/Makefile
])

AC_OUTPUT
