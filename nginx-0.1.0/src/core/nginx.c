
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
    ngx_list_t list;
    ngx_list_part_t *part;
    ngx_uint_t *data, *e, i;

    log = ngx_log_init_stderr();
    
    ngx_os_init(log);

    pool = ngx_create_pool(1024, log);

    ngx_list_init(&list, pool, 3, sizeof(ngx_uint_t));

    for (i = 0; i < 10; ++i) {
        e = ngx_list_push(&list);
        *e = i * 2;
    }

    part = &list.part;
    data = part->elts;

    for (i = 0; /* void */; i++) {
        
        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            data = part->elts;
            i = 0;
        }

        printf("%lu\n", (unsigned long) data[i]);
    }

    ngx_destroy_pool(pool);

    return 0;
}
