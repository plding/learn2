
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


ngx_int_t ngx_os_init(ngx_log_t *log)
{
    return ngx_posix_init(log);
}
