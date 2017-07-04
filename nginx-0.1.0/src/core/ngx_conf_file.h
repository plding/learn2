
/*
 * Copyright (C) Dingpeilong
 */


#ifndef _NGX_CONF_FILE_H_INCLUDED_
#define _NGX_CONF_FILE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


struct ngx_open_file_s {
    ngx_fd_t   fd;
    ngx_str_t  name;
};


struct ngx_module_s {
    ngx_uint_t       ctx_index;
};


ngx_open_file_t *ngx_conf_open_file(ngx_cycle_t *cycle, ngx_str_t *name);


#endif /* _NGX_CONF_FILE_H_INCLUDED_ */
