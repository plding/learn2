
/*
 * Copyright (C) Dingpeilong
 */


#ifndef _NGX_CONF_FILE_H_INCLUDED_
#define _NGX_CONF_FILE_H_INCLUDED_


struct ngx_open_file_s {
    ngx_fd_t   fd;
    ngx_str_t  name;
};


struct ngx_module_s {
    ngx_uint_t       ctx_index;
};


#endif /* _NGX_CONF_FILE_H_INCLUDED_ */
