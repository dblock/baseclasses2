AC_INIT([baseclasses2], [1.0])
AC_CONFIG_MACRO_DIR([m4])

echo "Running baseclasses2 Configuration Script"

BC_CHECK_PLATFORM
BC_GCC_CHECK
BC_MAKE_CHECK

AC_PROG_MAKE_SET
AC_C_BIGENDIAN
AC_CHECK_SIZEOF([int])

BC_GCC_SUPPORTS_OPTIONS([Wall Wno-uninitialized Wno-deprecated])
BC_GCC_SUPPORTS_OPTIONS_EXCLUSIVE([O3 O2 O1])

AC_CHECK_HEADERS([unistd.h strings.h])
AC_TYPE_SIZE_T

AC_CONFIG_HEADERS([platform/config.hpp])
AC_CONFIG_FILES([Makefile Makefile.each])
AC_OUTPUT
