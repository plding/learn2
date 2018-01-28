/*
 * Wrapper functions for our own library functions.
 * Most are included in the source file for the function itself.
 */

#include    "unp.h"

const char *
Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
    const char  *ptr;

    if (strptr == NULL)
        err_quit("NULL 3rd argument to inet_ntop");
    if ( (ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
        err_sys("inet_ntop error");     /* sets errno */
    return(ptr);
}
