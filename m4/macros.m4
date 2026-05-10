#
#  autoconf macros for baseclasses2
#  Originally: Vestris Inc., Geneva, Switzerland, 1994-1999
#  Renamed from aclocal.m4 to m4/macros.m4
#

# Detect platform OS name and set thread-safe defines
AC_DEFUN([BC_CHECK_PLATFORM_BASE],[
  AC_DEFINE([_REENTRANT])
  AC_DEFINE([_POSIX_PTHREAD_SEMANTICS])
  AC_DEFINE([_THREAD_SAFE])
  baselib_platform=`uname | cut -f1 -d'/' | sed -e 's/[[^a-zA-Z0-9_]]//g'`
  BASEOS=$baselib_platform
  AC_SUBST([BASEOS])
  case $PLATFORM in
    *-*-irix* )
      AC_DEFINE([_SGI_MP_SOURCE])
      AC_DEFINE([_BSD_TYPES])
      AC_DEFINE([_POSIX_C_SOURCE], [199506L])
      ;;
    *-*-bsd* )
      AC_DEFINE([_POSIX_C_SOURCE], [199506L])
      ;;
  esac
  AC_MSG_RESULT([operating system: $BASEOS])
  BASEPROC=`echo $PLATFORM | cut -f1 -d'-' | sed -e 's/i[[0-9]]86/x86/g'`
  AC_MSG_RESULT([processor: $BASEPROC])
  AC_SUBST([BASEPROC])
])

# Detect the full platform triple and call BC_CHECK_PLATFORM_BASE
AC_DEFUN([BC_CHECK_PLATFORM],[
  AC_MSG_CHECKING([platform])
  PLATFORM=`${CONFIG_SHELL-/bin/sh} ./config.guess`
  PLATFORM=`${CONFIG_SHELL-/bin/sh} ./config.sub $PLATFORM`
  AC_SUBST([PLATFORM])
  AC_MSG_RESULT([$PLATFORM])
  BC_CHECK_PLATFORM_BASE
])

# Determine the PATH separator (: on Unix, ; on DOS)
AC_DEFUN([BC_SET_PATH_SEPARATOR],[
  if test "X${PATH_SEPARATOR+set}" != "Xset"; then
    UNAME=${UNAME-`uname 2>/dev/null`}
    case X$UNAME in
      *-DOS) PATH_SEPARATOR=';' ;;
      *)     PATH_SEPARATOR=':' ;;
    esac
  fi
])

# Locate g++ or gcc and export as GCC
AC_DEFUN([BC_GCC_CHECK],[
  BC_SET_PATH_SEPARATOR
  if test -z "$CC"; then
    AC_MSG_CHECKING([for g++])
    IFS="${IFS= }"; save_ifs="$IFS"; IFS="${IFS}${PATH_SEPARATOR}"
    for dir in $PATH; do
      test -z "$dir" && dir=.
      if test -f $dir/g++; then
        CC="$dir/g++"; break
      elif test -f $dir/gcc; then
        CC="$dir/gcc"
      fi
    done
    IFS="$save_ifs"
    if test -n "$CC"; then
      AC_MSG_RESULT([$CC])
    else
      AC_MSG_RESULT([no])
    fi
  fi
  GCC=$CC
  AC_SUBST([GCC])
])

# Locate GNU make or gmake and export as MAKE
AC_DEFUN([BC_MAKE_CHECK],[
  BC_SET_PATH_SEPARATOR
  if test -z "$MAKE"; then
    AC_MSG_CHECKING([for make])
    IFS="${IFS= }"; save_ifs="$IFS"; IFS="${IFS}${PATH_SEPARATOR}"
    for dir in $PATH; do
      test -z "$dir" && dir=.
      if test -f $dir/make && (`$dir/make --version | grep GNU > /dev/null`); then
        MAKE="$dir/make"; break
      elif test -f $dir/gmake && (`$dir/gmake --version | grep GNU > /dev/null`); then
        MAKE="$dir/gmake"
      fi
    done
    IFS="$save_ifs"
    if test -n "$MAKE"; then
      AC_MSG_RESULT([$MAKE])
    else
      AC_MSG_RESULT([no])
    fi
  fi
  AC_SUBST([MAKE])
])

# Check whether g++ accepts a single option; append to CPPFLAGS if so
AC_DEFUN([BC_GCC_SUPPORTS_OPTION],[
  ac_cached_name=`echo $1 | sed 's/-/_/g'`
  AC_MSG_CHECKING([whether $CC supports -$1])
  AC_CACHE_VAL([ac_cv_compile_$ac_cached_name],[
    save_CFLAGS=$CFLAGS
    echo "int some_variable = 0;" > conftest.c
    CFLAGS="$CFLAGS -$1 -c conftest.c"
    if $CC $CFLAGS 2>conftest.err && test ! -s conftest.err; then
      eval ac_cv_compile_$ac_cached_name=yes
    else
      eval ac_cv_compile_$ac_cached_name=no
    fi
    rm -f conftest*
    CFLAGS=$save_CFLAGS
  ])
  eval compiler_option=\$ac_cv_compile_$ac_cached_name
  if test "$compiler_option" = "yes"; then
    CPPFLAGS="$CPPFLAGS -$1"
  fi
  AC_MSG_RESULT([$compiler_option])
])

# Check a list of options, adding each supported one to CPPFLAGS
AC_DEFUN([BC_GCC_SUPPORTS_OPTIONS],[
  for option in $1; do
    AC_MSG_CHECKING([whether $CC supports -$option])
    echo "int some_variable = 0;" > conftest.c
    if $CC -$option -c conftest.c -o conftest.o > /dev/null 2>&1; then
      CPPFLAGS="$CPPFLAGS -$option"
      AC_MSG_RESULT([yes])
    else
      AC_MSG_RESULT([no])
    fi
    rm -f conftest.c conftest.o
  done
])

# Check a list of options, stopping at the first supported one
AC_DEFUN([BC_GCC_SUPPORTS_OPTIONS_EXCLUSIVE],[
  for option in $1; do
    AC_MSG_CHECKING([whether $CC supports -$option])
    echo "int some_variable = 0;" > conftest.c
    if $CC -$option -c conftest.c -o conftest.o > /dev/null 2>&1; then
      CPPFLAGS="$CPPFLAGS -$option"
      AC_MSG_RESULT([yes])
      rm -f conftest.c conftest.o
      break
    else
      AC_MSG_RESULT([no])
    fi
    rm -f conftest.c conftest.o
  done
])
