
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <nginx.h>


int main(int argc, char *const *argv)
{
    ngx_log_t *log = ngx_log_init_stderr();

    char *p = ngx_alloc(10, log);
    char *q = ngx_memalign(4096, 10, log);

    return 0;
}
