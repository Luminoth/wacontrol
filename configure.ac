#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([WinAmp Controller], [1.0.0], [energon@mindspring.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([src/WACApplication.h])
AC_CONFIG_HEADER([config.h])

# Automake configuration
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE  # this isn't necessarily safe

# Report what we're configuring
echo
AS_BOX([Configuring ${PACKAGE}-${VERSION}])
echo

# Make sure top_builddir is setup correctly (for AC_PROG_LIBTOOL)
for top_builddir in . .. ../.. $ac_auxdir $ac_auxdir/..; do
    test -f $top_builddir/configure && break
done

# Enable options
AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug], [compile with debugging support [[default=no]]]), enable_debug=yes, enable_debug=no)
AC_ARG_ENABLE(efence, AC_HELP_STRING([--enable-efence], [compile with electric fence support [[default=no]]]), enable_efence=yes, enable_efence=no)
AC_ARG_ENABLE(profile, AC_HELP_STRING([--enable-profile], [compile with profiling support [[default=no]]]), enable_profile=yes, enable_profile=no)

AC_CANONICAL_HOST

# Host vars
USE_LINUX=0

# Host flags
case "${host}" in
*-*-linux-gnu*)
    echo "Setting Linux compilation options"

    CXXFLAGS="${CXXFLAGS} -Wall -Wstrict-prototypes -Woverloaded-virtual -pipe -D_REENTRANT `pkg-config gtkmm-2.4 --cflags`"

    USE_LINUX=1
    ;;
*)
    AC_MSG_ERROR([${host} not supported!])
    ;;
esac

if test "$enable_debug" = yes; then
    CXXFLAGS="${CXXFLAGS} -g -gstabs+ -fno-default-inline"
    AC_DEFINE(DEBUG, 1, [Define to 1 for debugging.])
else
    CXXFLAGS="${CXXFLAGS} -O3 -finline-functions -ffast-math -fno-common -funroll-loops"
    AC_DEFINE(NDEBUG, 1, [Define to 1 for not debugging.])
fi

if test "$enable_efence" = yes; then
    LIBS="${LIBS} -lefence"
fi

if test "$enable_profile" = yes; then
    LDFLAGS="${LDFLAGS} -pg"
    CXXFLAGS="${CXXFLAGS} -pg"
fi

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
#AC_CHECK_HEADERS([],, AC_MSG_ERROR([A C header was not found]))

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_SELECT_ARGTYPES
AC_CHECK_FUNCS([select socket],, AC_MSG_ERROR([A C function was not found]))

AC_LANG_PUSH([C++])

# Checks for header files.
AC_CHECK_HEADERS([cassert string cstdlib],, AC_MSG_ERROR([A C++ header was not found]))

AC_LANG_POP([C++])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

# Report configuration
AC_ENERGON_OUTPUT
