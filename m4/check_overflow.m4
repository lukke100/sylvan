AC_DEFUN([CHECK_OVERFLOW_BUILTIN], [
	AC_MSG_CHECKING([for $1])
	AC_LINK_IFELSE(
		[AC_LANG_PROGRAM([[]], [[
			int out;
			return $1(1, 1, &out);
		]])],
		[
			AC_MSG_RESULT([yes])
			AC_DEFINE(AS_TR_CPP([HAVE_$1]), [1], [$1 exists])
		],
		[AC_MSG_RESULT([no])]
	)
])
