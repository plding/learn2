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

#include "php_dpl.h"

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_dctype_alnum, 0)
    ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ dpl_functions[]
 * Every user visible function must have an entry in dpl_functions[].
 */
const zend_function_entry dpl_functions[] = {
    PHP_FE(dctype_alnum, arginfo_dctype_alnum)
    PHP_FE_END
};
/* }}} */

/* {{{ dpl_module_entry
 */
zend_module_entry dpl_module_entry = {
    STANDARD_MODULE_HEADER,
    "dpl",
    dpl_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_DPL_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DPL
ZEND_GET_MODULE(dpl)
#endif
