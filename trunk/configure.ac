#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([Frog Framework], [0.1], [janvier@users.berlios.de])
AC_CONFIG_SRCDIR([src/AddressFamily.cpp])
AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE
AM_PATH_CPPUNIT(1.10.2)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_GCC_TRADITIONAL
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_PROG_RANLIB

# Checks for libraries.
AC_SEARCH_LIBS([socket], [socket])
AC_SEARCH_LIBS([inet_ntop], [nsl])
AC_SEARCH_LIBS([inet_pton], [nsl])
AC_SEARCH_LIBS([inet_ntoa], [nsl])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h stdint.h inttypes.h sys/socket.h sys/ioctl.h ifaddrs.h])
AC_CHECK_HEADERS([unistd.h stropts.h sys/sockio.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_HEADER_TIME
AC_C_CONST
AC_C_LONG_LONG
AC_C_TIMESPEC
AX_CREATE_STDINT_H(src/frog/stdint.h)

# Checks for library functions.
AC_FUNC_MEMCMP
AC_HEADER_STDC
AC_CHECK_FUNCS([memset strerror inet_aton inet_ntoa inet_pton inet_ntop gettimeofday socket])

AC_ARG_ENABLE(ipv6, 
			  [AC_HELP_STRING([--enable-ipv6], 
							  [turn on IPv6 support [default=no]])],
			  [AC_DEFINE([HAVE_IPV6_SUPPORT], [1], [Define 1 if your system supports IPv6.])])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
