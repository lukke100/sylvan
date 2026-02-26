AC_PREREQ([2.71])
AC_INIT([sylvan],[0.1],[lukke100@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_EXTRA_RECURSIVE_TARGETS([bench])
AC_CONFIG_SRCDIR([include/sylvan.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_USE_SYSTEM_EXTENSIONS
AC_PROG_CC
AM_PROG_AR
LT_INIT

# Checks for libraries.
LIBS_TMP="$LIBS"
BENCH_LIBS=""

AC_SEARCH_LIBS([clock_gettime], [rt], [
	AS_IF([test "$ac_cv_search_clock_gettime" != "none required"], [
		BENCH_LIBS="$ac_cv_search_clock_gettime"
	])

	AC_DEFINE([HAVE_CLOCK_GETTIME], [1], [clock_gettime exists])
])

LIBS="$LIBS_TMP"
AC_SUBST([BENCH_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([limits.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

m4_foreach([type], [[long], [int], [size_t], [unsigned long], [unsigned]], [
	CHECK_BUILTIN_OVERFLOW([__builtin_add_overflow], type)
	CHECK_BUILTIN_OVERFLOW([__builtin_sub_overflow], type)
	CHECK_BUILTIN_OVERFLOW([__builtin_mul_overflow], type)
])

# Checks for library functions.
AC_CHECK_FUNCS([memcpy])

AC_CONFIG_FILES([
	Makefile
	bench/Makefile
	include/Makefile
	src/Makefile
	tests/Makefile
])
AC_OUTPUT
