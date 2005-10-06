dnl @synopsis AC_C_TIMESPEC
dnl
dnl Provide a test for the existance of struct timespec and
dnl define HAVE_STRUCT_TIMESPEC if it is found
dnl
dnl @category C
dnl @author Jim Meyering
dnl @version
dnl @license AllPermisive

AC_DEFUN([AC_C_TIMESPEC],
[
  AC_LIBSOURCES([timespec.h])

  dnl Prerequisites of lib/timespec.h.
  AC_REQUIRE([AC_C_INLINE])
  AC_REQUIRE([AC_HEADER_TIME])
  AC_CHECK_HEADER([sys/time.h])
  AC_C_CHECK_TYPE_STRUCT_TIMESPEC
])

dnl Define HAVE_STRUCT_TIMESPEC if `struct timespec' is declared
dnl in time.h or sys/time.h.

AC_DEFUN([AC_C_CHECK_TYPE_STRUCT_TIMESPEC],
[
  AC_REQUIRE([AC_HEADER_TIME])
  AC_CHECK_HEADER([sys/time.h])
  AC_CACHE_CHECK([for struct timespec], fu_cv_sys_struct_timespec,
    [AC_TRY_COMPILE(
      [
#      if TIME_WITH_SYS_TIME
#       include <sys/time.h>
#       include <time.h>
#      else
#       if HAVE_SYS_TIME_H
#        include <sys/time.h>
#       else
#        include <time.h>
#       endif
#      endif
      ],
      [static struct timespec x; x.tv_sec = x.tv_nsec;],
      fu_cv_sys_struct_timespec=yes,
      fu_cv_sys_struct_timespec=no)
    ])

  if test $fu_cv_sys_struct_timespec = yes; then
    AC_DEFINE(HAVE_STRUCT_TIMESPEC, 1,
              [Define if struct timespec is declared in <time.h>. ])
  fi
])
