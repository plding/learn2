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

#ifndef PHP_DPL_CTYPE_H
#define PHP_DPL_CTYPE_H

#if HAVE_DPL_CTYPE

extern zend_module_entry dpl_ctype_module_entry;
#define phpext_dpl_ctype_ptr &dpl_ctype_module_entry

PHP_MINFO_FUNCTION(dpl_ctype);

PHP_FUNCTION(dpl_ctype_alnum);

#else

#define phpext_dpl_ctype_ptr NULL

#endif

#endif   /* PHP_DPL_CTYPE_H */
