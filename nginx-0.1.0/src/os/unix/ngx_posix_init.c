
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


#if (NGX_POSIX_IO)

ngx_int_t ngx_os_init(ngx_log_t *log)
{
    return ngx_posix_init(log);
}


#endif


ngx_int_t ngx_posix_init(ngx_log_t *log)
{
    ngx_pagesize = getpagesize();

    return NGX_OK;
}
