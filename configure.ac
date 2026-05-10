AC_INIT([baseclasses2], [1.0])
AC_CONFIG_MACRO_DIR([m4])
m4_include([m4/macros.m4])

echo "Running baseclasses2 Configuration Script"

AC_PROG_CXX
BC_MAKE_CHECK

AC_PROG_MAKE_SET

BC_GCC_SUPPORTS_OPTIONS([Wall Wno-uninitialized Wno-deprecated])
BC_GCC_SUPPORTS_OPTIONS_EXCLUSIVE([O3 O2 O1])

AC_CONFIG_FILES([Makefile Makefile.each])
AC_OUTPUT
