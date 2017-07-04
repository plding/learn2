
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


ngx_open_file_t *ngx_conf_open_file(ngx_cycle_t *cycle, ngx_str_t *name)
{
    ngx_open_file_t  *file;

    if (!(file = ngx_list_push(&cycle->open_files))) {
        return NULL;
    }

    file->fd = ngx_stderr_fileno;
    file->name.len = 0;
    file->name.data = NULL;

    return file;
}
