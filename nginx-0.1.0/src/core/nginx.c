
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
    ngx_array_t *a;
    ngx_uint_t *e, i;

    log = ngx_log_init_stderr();
    
    ngx_os_init(log);

    pool = ngx_create_pool(1024, log);

    a = ngx_array_create(pool, 10, sizeof(ngx_uint_t));

    for (i = 0; i < a->nalloc; ++i) {
        e = ngx_array_push(a);
        *e = i * 2;
    }

    for (i = 0; i < a->nelts; ++i) {
        printf("%lu\n", (unsigned long) *((ngx_uint_t *) a->elts + i));
    }

    ngx_destroy_pool(pool);

    return 0;
}
