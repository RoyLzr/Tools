//**********************************************************
//          Net Utility 1.0
//
//  Description:
//  ���� ���� ����
//
// Author: Liu ZhaoRui
//         liuzhaorui1@163.com
//**********************************************************

#ifndef __NET_H__
#define __NET_H__

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <endian.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <netinet/tcp.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <signal.h>
#include <limits.h>

typedef struct _rio_t
{
    int rio_fd;
    int rio_cnt;
    size_t rio_len;
    char * rio_bufptr;
    char * rio_ptr;

    char * cache;
    int cache_len;
} rio_t;

void  
rio_init(rio_t *rp, int fd, int len);

ssize_t 
rio_readn(rio_t *rp, void *usrbuf, size_t n, int * st = NULL);

ssize_t
rio_readline(rio_t *rp, void *usrbuf, size_t maxlen, int * st = NULL);

ssize_t
sendn(int fd, void *usrbuf, size_t n);

int 
set_fd(int fd, int flags, int closed);

int 
set_fd_noblock(int fd);

int
set_tcp_sockaddr(char * addr, int port, 
                 struct sockaddr_in * soin);

const char *
get_tcp_sockaddr(char * addr, int * port, 
                 struct sockaddr_in * soin, int len);

int
net_connect_to_tv(int fd, const sockaddr * sa, 
                socklen_t socklen, timeval * tv, int isclose = 1);


int
net_connect_to_ms(int sockfd, const struct sockaddr *sa, 
                  socklen_t socklen, int msecs, int isclose = 1);


int
net_accept(int sockfd, struct sockaddr *sa, socklen_t * addrlen);


int
net_tcplisten(int port, int queue);


ssize_t 
readn_to_ms(int fd, void *ptr, size_t nbytes, int msecs);


ssize_t 
rio_readn_to_ms(rio_t *rp, void *usrbuf, size_t n, int msecs);


ssize_t
rio_readline_to_ms(rio_t *rp, void *usrbuf, size_t maxlen, int msecs);


ssize_t 
sendn_to_ms(int sock, const void *ptr, size_t nbytes, int msecs);

#endif
