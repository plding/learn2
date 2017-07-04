
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


#ifdef NGX_ERROR_LOG_PATH
static ngx_str_t  error_log = ngx_string(NGX_ERROR_LOG_PATH);
#else
static ngx_str_t  error_log = ngx_null_string;
#endif


ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle)
{
    ngx_uint_t          n;
    ngx_log_t          *log;
    ngx_pool_t         *pool;
    ngx_cycle_t        *cycle;
    ngx_list_part_t    *part;

    log = old_cycle->log;

    if (!(pool = ngx_create_pool(16 * 1024, log))) {
        return NULL;
    }
    pool->log = log;

    if (!(cycle = ngx_pcalloc(pool, sizeof(ngx_cycle_t)))) {
        ngx_destroy_pool(pool);
        return NULL;
    }
    cycle->pool = pool;
    cycle->log = log;
    cycle->old_cycle = old_cycle;


    if (old_cycle->open_files.part.nelts) {
        n = old_cycle->open_files.part.nelts;
        for (part = old_cycle->open_files.part.next; part; part = part->next) {
            n += part->nelts;
        }

    } else {
        n = 20;
    }

    if (ngx_list_init(&cycle->open_files, pool, n, sizeof(ngx_open_file_t))
                                                                  == NGX_ERROR)
    {
        ngx_destroy_pool(pool);
        return NULL;
    }


    if (!(cycle->new_log = ngx_log_create_errlog(cycle, NULL))) {
        ngx_destroy_pool(pool);
        return NULL;
    }

    cycle->new_log->file->name = error_log;

    return cycle;
}
