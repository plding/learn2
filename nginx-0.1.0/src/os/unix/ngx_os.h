
/*
 * Copyright (C) Dingpeilong
 */


#ifndef _NGX_OS_H_INCLUDED_
#define _NGX_OS_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


ngx_int_t ngx_os_init(ngx_log_t *log);
ngx_int_t ngx_posix_init(ngx_log_t *log);


#define ngx_stderr_fileno  STDERR_FILENO

#ifdef __linux__
#include <ngx_linux.h>
#endif


#endif /* _NGX_OS_H_INCLUDED_ */
