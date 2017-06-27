dnl
dnl $Id$
dnl

PHP_ARG_ENABLE(dpl_ctype, whether to enable dpl_ctype functions,
[  --enable-dpl_ctype         Enable dpl_ctype functions], no)

if test "$PHP_DPL_CTYPE" != "no"; then
  AC_DEFINE(HAVE_DPL_CTYPE, 1, [ ])
  PHP_NEW_EXTENSION(dpl_ctype, dpl_ctype.c, $ext_shared)
fi
