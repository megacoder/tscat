#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([tscat], [0.0.0], [Tommy Reynolds <Tommy.Reynolds@Megacoder.com>])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADER([src/config.h])
AC_CONFIG_MACRO_DIR([m4])

#
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

#
AM_MAINTAINER_MODE
#

#
AC_CONFIG_FILES([
	Makefile
	tscat.spec
	src/Makefile
])
AC_OUTPUT
