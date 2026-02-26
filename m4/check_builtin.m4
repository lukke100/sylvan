AC_DEFUN([CHECK_BUILTIN_OVERFLOW], [
	AC_REQUIRE([AC_PROG_CC])
	AC_MSG_CHECKING([for $1 on $2])

	m4_pushdef([TEST_PROG], [AC_LANG_PROGRAM([[
		#include <stddef.h>
	]], [[
		$2 result;
		(void)$1(($2)1, ($2)1, &result);
		(void)result;
	]])])

	m4_pushdef([LINK_PASS], [
		AC_MSG_RESULT([yes])
		AC_DEFINE(AS_TR_CPP([HAVE_$1_$2]), [1], [$1 takes $2])
	])

	m4_pushdef([LINK_FAIL], [AC_MSG_RESULT([no])])

	AC_LANG_PUSH([C])
	AC_LINK_IFELSE([TEST_PROG], [LINK_PASS], [LINK_FAIL])
	AC_LANG_POP([C])

	m4_popdef([LINK_FAIL])
	m4_popdef([LINK_PASS])
	m4_popdef([TEST_PROG])
])
