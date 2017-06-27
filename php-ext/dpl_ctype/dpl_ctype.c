/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2015 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Dingpeilon <77676182@qq.com>                                 |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_dpl_ctype.h"
#include "ext/standard/info.h"

#include <ctype.h>

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_dpl_ctype_alnum, 0)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ dpl_ctype_functions[]
 * Every user visible function must have an entry in dpl_ctype_functions[].
 */
static const zend_function_entry dpl_ctype_functions[] = {
    PHP_FE(dpl_ctype_alnum, arginfo_dpl_ctype_alnum)
    PHP_FE_END
};
/* }}} */

/* {{{ dpl_ctype_module_entry
 */
zend_module_entry dpl_ctype_module_entry = {
    STANDARD_MODULE_HEADER,
    "dpl_ctype",
    dpl_ctype_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_MINFO(dpl_ctype),
    "1.0",
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DPL_CTYPE
ZEND_GET_MODULE(dpl_ctype)
#endif

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(dpl_ctype)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "dpl_ctype functions", "enabled");
    php_info_print_table_end();
}
/* }}} */

/* {{{ DPL_CTYPE
 */
#define DPL_CTYPE(iswhat) \
    zval *c, tmp; \
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &c) == FAILURE) \
        return; \
    if (Z_TYPE_P(c) == IS_LONG) { \
        if (Z_LVAL_P(c) <= 255 && Z_LVAL_P(c) >= 0) { \
            RETURN_BOOL(iswhat(Z_LVAL_P(c))); \
        } else if (Z_LVAL_P(c) >= -128 && Z_LVAL_P(c) < 0) { \
            RETURN_BOOL(iswhat(Z_LVAL_P(c) + 256)); \
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
    }

/* }}} */

/* {{{ proto bool dpl_ctype_alnum(mixed c)
   Checks for alphanumberic character(s) */
PHP_FUNCTION(dpl_ctype_alnum)
{
    DPL_CTYPE(isalnum);
}
/* }}} */
