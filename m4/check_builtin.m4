AC_DEFUN([CHECK_BUILTIN_COMMON], [
	AC_REQUIRE([AC_PROG_CC])
	AC_MSG_CHECKING([for $1 on $2])

	AC_LANG_PUSH([C])
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[
		#include <stddef.h>
	]],
		[$3]
	)], [
		AC_MSG_RESULT([yes])
		AC_DEFINE(AS_TR_CPP([HAVE_$1_$2]), [1], [$1 takes $2])
	], [
		AC_MSG_RESULT([no])
	])
	AC_LANG_POP([C])
])

AC_DEFUN([CHECK_BUILTIN_OVERFLOW], [
	CHECK_BUILTIN_COMMON([$1], [$2], [[
		$2 res;
		int err;
		err = $1(($2)1, ($2)1, &res);
		(void)err;
		(void)res;
	]])
])

AC_DEFUN([CHECK_BUILTIN_BITS], [
	CHECK_BUILTIN_COMMON([$1], [$2], [[
		int result;
		result = $1(($2)1);
		(void)result;
	]])
])
