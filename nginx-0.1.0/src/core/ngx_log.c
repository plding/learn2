
/*
 * Copyright (C) Dingpeilong
 */


#include <ngx_config.h>
#include <ngx_core.h>


static void ngx_log_write(ngx_log_t *log, char *errstr, size_t len);


static ngx_log_t        ngx_log;
static ngx_open_file_t  ngx_stderr;


static const char *err_levels[] = {
    "stderr", "emerg", "alert", "crit", "error",
    "warn", "notice", "info", "debug"
};

static const char *debug_levels[] = {
    "debug_core", "debug_alloc", "debug_mutex", "debug_event",
    "debug_http", "debug_imap"
};


#if (HAVE_VARIADIC_MACROS)
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
                        const char *fmt, ...)
#else
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
                        const char *fmt, va_list args)
#endif
{
    char      errstr[MAX_ERROR_STR];
    size_t    len, max;
#if (HAVE_VARIADIC_MACROS)
    va_list   args;
#endif

    if (log->file->fd == NGX_INVALID_FILE) {
        return;
    }

    max = MAX_ERROR_STR - 1;

    len = ngx_snprintf(errstr, max, "[%s] ", err_levels[level]);

#if (HAVE_VARIADIC_MACROS)

    va_start(args, fmt);
    len += ngx_vsnprintf(errstr + len, max - len, fmt, args);
    va_end(args);

#else

    len += ngx_vsnprintf(errstr + len, max - len, fmt, args);

#endif

    if (len >= max) {
        ngx_log_write(log, errstr, max);
        return;
    }

    ngx_log_write(log, errstr, len);
}


static void ngx_log_write(ngx_log_t *log, char *errstr, size_t len)
{
    errstr[len++] = LF;
    write(log->file->fd, errstr, len);
}


#if !(HAVE_VARIADIC_MACROS)

void ngx_log_error(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
                   const char *fmt, ...)
{
    va_list    args;

    if (log->log_level >= level) {
        va_start(args, fmt);
        ngx_log_error_core(level, log, err, fmt, args);
        va_end(args);
    }
}


void ngx_log_debug_core(ngx_log_t *log, ngx_err_t err, const char *fmt, ...)
{
    va_list    args;

    va_start(args, fmt);
    ngx_log_error_core(NGX_LOG_DEBUG, log, err, fmt, args);
    va_end(args);
}


void ngx_assert_core(ngx_log_t *log, const char *fmt, ...)
{
    va_list    args;

    va_start(args, fmt);
    ngx_log_error_core(NGX_LOG_ALERT, log, 0, fmt, args);
    va_end(args);
}

#endif


ngx_log_t *ngx_log_init_stderr()
{
    ngx_stderr.fd = STDERR_FILENO;

    ngx_log.file = &ngx_stderr;
    ngx_log.log_level = NGX_LOG_DEBUG_ALL;

    return &ngx_log;
}


ngx_log_t *ngx_log_create_errlog(ngx_cycle_t *cycle, ngx_array_t *args)
{
    ngx_log_t  *log;

    if (!(log = ngx_pcalloc(cycle->pool, sizeof(ngx_log_t)))) {
        return NULL;
    }

    if (!(log->file = ngx_conf_open_file(cycle, NULL))) {
        return NULL;
    }

    return log;
}
