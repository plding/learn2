
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <nginx.h>


int main(int argc, char *const *argv)
{
    ngx_log_t *log;
    ngx_pool_t *pool;
    u_char *p, *q, *s;

    log = ngx_log_init_stderr();
    
    ngx_os_init(log);

    pool = ngx_create_pool(1024, log);

    p = ngx_palloc(pool, 10);
    q = ngx_palloc(pool, 2048);
    s = ngx_palloc(pool, 2048);

    ngx_destroy_pool(pool);

    return 0;
}
