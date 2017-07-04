
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <nginx.h>


volatile ngx_cycle_t  *ngx_cycle;


int main(int argc, char *const *argv)
{
    ngx_log_t         *log;
    ngx_cycle_t       *cycle, init_cycle;

    if (!(log = ngx_log_init_stderr())) {
        return 1;
    }

    ngx_memzero(&init_cycle, sizeof(ngx_cycle_t));
    init_cycle.log = log;
    ngx_cycle = &init_cycle;

    if (!(init_cycle.pool = ngx_create_pool(1024, log))) {
        return 1;
    }

    log->log_level = NGX_LOG_DEBUG_ALL;

    if (ngx_os_init(log) == NGX_ERROR) {
        return 1;
    }

    cycle = ngx_init_cycle(&init_cycle);
    if (cycle == NULL) {
        return 1;
    }

    return 0;
}
