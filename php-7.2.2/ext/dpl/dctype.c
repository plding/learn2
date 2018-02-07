/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2018 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Ding Peilong <77676182@qq.com>                               |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_dctype.h"

#include <ctype.h>

/* {{{ dctype
 */
#define DCTYPE(iswhat) \
    zval *c, tmp; \
    ZEND_PARSE_PARAMETERS_START(1, 1); \
        Z_PARAM_ZVAL(c) \
    ZEND_PARSE_PARAMETERS_END(); \
    if (Z_TYPE_P(c) == IS_LONG) { \
        if (Z_LVAL_P(c) <= 255 && Z_LVAL_P(c) >= 0) { \
            RETURN_BOOL(iswhat((int) Z_LVAL_P(c))); \
        } else if (Z_LVAL_P(c) >= -128 && Z_LVAL_P(c) < 0) { \
            RETURN_BOOL(iswhat((int) Z_LVAL_P(c) + 256)); \
        } \
        tmp = *c; \
        zval_copy_ctor(&tmp); \
        convert_to_string(&tmp); \
    } else { \
        tmp = *c; \
    } \
    if (Z_TYPE(tmp) == IS_STRING) { \
        char *p = Z_STRVAL(tmp), *e = Z_STRVAL(tmp) + Z_STRLEN(tmp); \
        if (e == p) { \
            if (Z_TYPE_P(c) == IS_LONG) zval_dtor(&tmp); \
            RETURN_FALSE; \
        } \
        while (p < e) { \
            if (!iswhat((int) *(unsigned char *)(p++))) { \
                if (Z_TYPE_P(c) == IS_LONG) zval_dtor(&tmp); \
                RETURN_FALSE; \
            } \
        } \
        if (Z_TYPE_P(c) == IS_LONG) zval_dtor(&tmp); \
        RETURN_TRUE; \
    } else { \
        RETURN_FALSE; \
    } \

/* }}} */

/* {{{ proto bool dctype_alnum(mixed c)
   Checks for alphanumeric character(s) */
PHP_FUNCTION(dctype_alnum)
{
    DCTYPE(isalnum);
}
/* }}} */
