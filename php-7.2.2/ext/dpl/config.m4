dnl
dnl $Id$
dnl

PHP_ARG_ENABLE(dpl, whether to enable dpl functions,
[  --enable-dpl			 Enable dpl functions], yes)

if test "$PHP_DPL" != "no"; then
  PHP_NEW_EXTENSION(dpl, dpl.c dctype.c, $ext_shared)
fi
