
/*
 * Copyright (C) Dingpeilong
 */


#ifndef _NGX_CONFIG_H_INCLUDED_
#define _NGX_CONFIG_H_INCLUDED_


#if defined __linux__
#include <ngx_linux_config.h>
#endif


/* TODO: platform specific: array[NGX_INVALID_ARRAY_INDEX] must cause SIGSEGV */
#define NGX_INVALID_ARRAY_INDEX 0x80000000


#if 1
/* STUB: autoconf */
typedef int                ngx_int_t;
typedef u_int              ngx_uint_t;
typedef int                ngx_flag_t;
#define NGX_INT_T_LEN      sizeof("-2147483648") - 1
#define NGX_INT_T_FMT      "d"
#define NGX_UINT_T_FMT     "u"

#else

typedef long               ngx_int_t;
typedef u_long             ngx_uint_t;
typedef long               ngx_flag_t;
#define NGX_INT_T_LEN      sizeof("-9223372036854775808") - 1
#define NGX_INT_T_FMT      "lld"
#define NGX_UINT_T_FMT     "llu"

#endif

/* TODO: auto */
#define NGX_INT32_LEN      sizeof("-2147483648") - 1
#define NGX_INT64_LEN      sizeof("-9223372036854775808") - 1
#define NGX_OFF_T_LEN      sizeof("-9223372036854775808") - 1


#endif /* _NGX_CONFIG_H_INCLUDED_ */
