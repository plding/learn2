
/*
 * Copyright (C) Dingpeilong
 */


#ifndef _NGX_CYCLE_H_INCLUDED_
#define _NGX_CYCLE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


struct ngx_cycle_s {
    ngx_pool_t        *pool;

    ngx_log_t         *log;
    ngx_log_t         *new_log;

    ngx_list_t         open_files;

    ngx_cycle_t       *old_cycle;
};


ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle);


extern volatile ngx_cycle_t  *ngx_cycle;


#endif /* _NGX_CYCLE_H_INCLUDED_ */
