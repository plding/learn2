#ifndef __unp_h
#define __unp_h

#include "../config.h"  /* configuration options for current OS */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <sys/select.h>
#include <poll.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <pthread.h>

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define LISTENQ     1024    /* 2nd argument to listen() */

/* Miscellaneous constants */
#define MAXLINE     4096    /* max text line length */

/* Following shortens all the typecasts of pointer arguments: */
#define SA  struct sockaddr

/* prototypes for our own library functions */
char    *sock_ntop(const SA *, socklen_t);

/* prototypes for our own library wrapper functions */
const char      *Inet_ntop(int, const void *, char *, size_t);
char    *Sock_ntop(const SA *, socklen_t);

/* prototypes for our Unix wrapper functions: see {Sec errors} */
void     Close(int);
void     Write(int, void *, size_t);

/* prototypes for our socket wrapper functions: see {Sec errors} */
int      Accept(int, SA *, socklen_t *);
void     Bind(int, const SA *, socklen_t);
void     Getsockname(int, SA *, socklen_t *);
void     Listen(int, int);
int      Socket(int, int, int);

void     err_dump(const char *, ...);
void     err_msg(const char *, ...);
void     err_quit(const char *, ...);
void     err_ret(const char *, ...);
void     err_sys(const char *, ...);

#endif  /* __unp_h */
