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

/* Miscellaneous constants */
#define MAXLINE     4096    /* max text line length */

/* Following shortens all the typecasts of pointer arguments: */
#define SA  struct sockaddr

void     err_dump(const char *, ...);
void     err_msg(const char *, ...);
void     err_quit(const char *, ...);
void     err_ret(const char *, ...);
void     err_sys(const char *, ...);

#endif  /* __unp_h */
