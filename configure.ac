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
PKG_CHECK_MODULES([WAYLAND_SERVER], [wayland-server])
PKG_CHECK_MODULES([TIZEN_COMMON], [capi-base-common, dlog])
PKG_CHECK_MODULES(WAYLAND_SCANNER, wayland-scanner)

PKG_CHECK_EXISTS([ecore],
                 [
                  AC_DEFINE([HAVE_ECORE], [1], [ecore support for tzsh])
                  have_ecore="yes"
                  requirement_tzsh_pc="ecore"
                 ],
                 [have_ecore="no"])
AM_CONDITIONAL([HAVE_ECORE], [test "x${have_ecore}" = "xyes"])

AC_MSG_CHECKING([whether to build efl for tzsh])
AC_MSG_RESULT([${have_ecore}])

PKG_CHECK_EXISTS([ecore-wayland],
                 [
                  AC_DEFINE([HAVE_ECORE_WAYLAND], [1], [ecore-wayland support for tzsh])
                  have_ecore_wayland="yes"
                  requirement_tzsh_pc="ecore-wayland"
                 ],
                 [have_ecore_wayland="no"])

AC_MSG_CHECKING([whether to build ecore-wayland backend])
AC_MSG_RESULT([${have_ecore_wayland}])

if test "x${have_ecore}" = "xyes"; then
   if test "x${have_ecore_wayland}" = "xyes"; then
      PKG_CHECK_MODULES([ECORE], [ecore ecore-wayland])
   else
      PKG_CHECK_MODULES([ECORE], [ecore])
   fi
fi

AC_ARG_WITH([tests],
   [AS_HELP_STRING([--with-tests=none|regular], [choose testing method: regular or none. @<:@default=none@:>@])],
   [build_tests=${withval}],
   [build_tests=none])

AC_MSG_CHECKING([whether to build tests for tzsh])
AC_MSG_RESULT([${build_tests}])

case "${build_tests}" in
   regular )
      want_tests="yes"
      ;;
   no* )
      ;;
   * )
      AC_MSG_ERROR([Unknown build tests option: --with-tests=${build_tests}])
      ;;
esac

if test "x${want_tests}" = "xyes"; then
   PKG_CHECK_MODULES([DAEMON], [wayland-server])
fi
AM_CONDITIONAL([TZSH_BUILD_TESTS], [test "x${want_tests}" = "xyes"])

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

AC_MSG_CHECKING([whether to build examples for tzsh])
AC_MSG_RESULT([${want_build_examples}])

if test "${want_build_examples}" = "yes"; then
   PKG_CHECK_MODULES([ELEMENTARY], [evas elementary])
fi

AC_CONFIG_FILES([
Makefile
pc/tzsh-server.pc
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
pc/tzsh-tvsrv.pc
pc/tzsh-tvsrv-service.pc
src/Makefile
src/lib/Makefile
src/examples/Makefile
src/tests/Makefile
])

AC_OUTPUT
