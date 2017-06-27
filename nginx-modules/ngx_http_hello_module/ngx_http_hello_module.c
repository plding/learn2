
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


typedef struct {
    ngx_str_t      hello_string;
    ngx_flag_t     hello_counter;
} ngx_http_hello_loc_conf_t;


static ngx_int_t ngx_http_hello_init(ngx_conf_t *cf);
static void *ngx_http_hello_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_hello_merge_loc_conf(ngx_conf_t *cf,
    void *parent, void *child);


static ngx_command_t  ngx_http_hello_commands[] = {
    
    { ngx_string("hello_string"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF
                        |NGX_CONF_TAKE1,
      ngx_conf_set_str_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_hello_loc_conf_t, hello_string),
      NULL },

    { ngx_string("hello_counter"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF
                        |NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_hello_loc_conf_t, hello_counter),
      NULL },

    ngx_null_command
};


static ngx_http_module_t  ngx_http_hello_module_ctx = {
    NULL,                                 /* preconfiguration */
    ngx_http_hello_init,                  /* postconfiguration */

    NULL,                                 /* create main configuration */
    NULL,                                 /* init main configuration */

    NULL,                                 /* create server configuration */
    NULL,                                 /* merge server configuration */

    ngx_http_hello_create_loc_conf,       /* create location configuration */
    ngx_http_hello_merge_loc_conf         /* merge location configuration */
};


ngx_module_t  ngx_http_hello_module = {
    NGX_MODULE_V1,
    &ngx_http_hello_module_ctx,           /* module context */
    ngx_http_hello_commands,              /* module directives */
    NGX_HTTP_MODULE,                      /* module type */
    NULL,                                 /* init master */
    NULL,                                 /* init module */
    NULL,                                 /* init process */
    NULL,                                 /* init thread */
    NULL,                                 /* exit thread */
    NULL,                                 /* exit process */
    NULL,                                 /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_int_t
ngx_http_hello_handler(ngx_http_request_t *r)
{
    ngx_int_t                   rc;
    ngx_buf_t                  *b;
    ngx_chain_t                 out;
    u_char                      greeting[1024] = {0};
    size_t                      length;
    ngx_http_hello_loc_conf_t  *hlcf;
    static int                  visited_times = 0;

    hlcf = ngx_http_get_module_loc_conf(r, ngx_http_hello_module);

    if (hlcf->hello_string.len == 0) {
        return NGX_DECLINED;
    }

    if (hlcf->hello_counter == 0) {
        ngx_sprintf(greeting, "%V", &hlcf->hello_string);
    } else {
        ngx_sprintf(greeting, "%V Visited Times: %d", &hlcf->hello_string,
            ++visited_times);
    }
    length = strlen((const char *) greeting);

    if (!(r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))) {
        return NGX_HTTP_NOT_ALLOWED;
    }

    rc = ngx_http_discard_request_body(r);

    if (rc != NGX_OK) {
        return rc;
    }

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = length;
    r->headers_out.content_type = (ngx_str_t) ngx_string("text/html");
    
    rc = ngx_http_send_header(r);
    
    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if (b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    b->pos = greeting;
    b->last = greeting + length;
    b->memory = 1;
    b->last_buf = 1;

    out.buf = b;
    out.next = NULL;

    return ngx_http_output_filter(r, &out);
}


static void *
ngx_http_hello_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_hello_loc_conf_t  *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_hello_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    /*
     * set by ngx_pcalloc():
     *
     *     conf->hello_string = { 0, NULL };
     */

    conf->hello_counter = NGX_CONF_UNSET;

    return conf;
}


static char *
ngx_http_hello_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_hello_loc_conf_t  *prev = parent;
    ngx_http_hello_loc_conf_t  *conf = child;

    ngx_conf_merge_str_value(conf->hello_string, prev->hello_string, "");
    ngx_conf_merge_value(conf->hello_counter, prev->hello_counter, 0);

    return NGX_CONF_OK;
}


static ngx_int_t
ngx_http_hello_init(ngx_conf_t *cf)
{
    ngx_http_handler_pt        *h;
    ngx_http_core_main_conf_t  *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    h = ngx_array_push(&cmcf->phases[NGX_HTTP_CONTENT_PHASE].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }

    *h = ngx_http_hello_handler;

    return NGX_OK;
}
