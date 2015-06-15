#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "../net.h"

#define max 128

using namespace std;
rio_t rio[2];
char res[10000];


//测试 server 阻塞 按行读，有cache
int test_block_cache(struct sockaddr_in server_address)
{
    int fd, epfd;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (sockaddr *) &server_address, sizeof(server_address));
    listen(listenfd, 10);
    
    struct epoll_event ev[2], events[1000];
  
    int confd0 = accept(listenfd, NULL, 0);
    cout << confd0 << endl; 
    int confd1 = accept(listenfd, NULL, 0);
    cout << confd1 << endl; 
    
    rio_init(&rio[0], confd0, 5);
    rio[0].rio_ptr = (char *) malloc(sizeof(char) * 5);
    
    rio_init(&rio[1], confd1, 5);
    rio[1].rio_ptr = (char *) malloc(sizeof(char) * 5);
   
    epfd = epoll_create(1000);

    ev[0].events = EPOLLIN;
    ev[0].data.fd = confd0;
    epoll_ctl(epfd, EPOLL_CTL_ADD, confd0, &ev[0]);
    
    ev[1].events = EPOLLIN;
    ev[1].data.fd = confd1;
    epoll_ctl(epfd, EPOLL_CTL_ADD, confd1, &ev[1]);
    
    for(;;)
    {
        cout << "waiting" << endl;
        int ndfs = epoll_wait(epfd, events, 1000, -1);
        cout << "wait end" << endl;
        for(int i = 0; i < ndfs; i++)
        {
            fd = events[i].data.fd;
            int idx = 1;
            if(fd == rio[0].rio_fd)
                idx = 0;
            int n = rio_readline(&rio[idx], res, sizeof(res));
            if(n == 0)
                return 0;
            //cout << "fd: " << rio[idx].rio_fd << ":"<< rio[idx].rio_cnt<< endl;
            
            cout << n <<" : " << res << endl; 
            cout << "write :" << sendn(fd, res, n) << endl;
            
            ev[0].events = events[i].events | EPOLLIN;
            ev[0].data.fd = fd;
            epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev[0]);
        }
    } 
}

//测试 server 非阻塞， 有cache, 一次请求的数据会尽可能多的读，读空cache
//修复 阻塞 有 cache 时候缺点， 一次cache read 得到多行， 但是上层readline, 只得到一行
//且剩余的行，存在 cache 里 epool 并不知道的缺点

int test_noblock_cache(struct sockaddr_in server_address)
{
    int fd, epfd;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (sockaddr *) &server_address, sizeof(server_address));
    listen(listenfd, 10);
    
    struct epoll_event ev[2], events[1000];
  
    int confd0 = accept(listenfd, NULL, 0);
    cout << confd0 << endl; 
    int confd1 = accept(listenfd, NULL, 0);
    cout << confd1 << endl; 
    
    set_fd_noblock(confd0);
    set_fd_noblock(confd1);

    rio_init(&rio[0], confd0, 5);
    rio[0].rio_ptr = (char *) malloc(sizeof(char) * 5);
    
    rio_init(&rio[1], confd1, 5);
    rio[1].rio_ptr = (char *) malloc(sizeof(char) * 5);
   
    epfd = epoll_create(1000);

    ev[0].events = EPOLLIN;
    ev[0].data.fd = confd0;
    epoll_ctl(epfd, EPOLL_CTL_ADD, confd0, &ev[0]);
    
    ev[1].events = EPOLLIN;
    ev[1].data.fd = confd1;
    epoll_ctl(epfd, EPOLL_CTL_ADD, confd1, &ev[1]);
    
    for(;;)
    {
        cout << "waiting" << endl;
        int ndfs = epoll_wait(epfd, events, 1000, -1);
        cout << "wait end" << endl;
        for(int i = 0; i < ndfs; i++)
        {
            fd = events[i].data.fd;
            int idx = 1;
            if(fd == rio[0].rio_fd)
                idx = 0;
            int n;
            int st;
            int clen = 0;
            if(rio[idx].cache != NULL )
            {
                memcpy(res, rio[idx].cache, rio[idx].cache_len);
                clen = rio[idx].cache_len;
                
                rio[idx].cache_len = 0;
                free(rio[idx].cache);
                rio[idx].cache = NULL;
            }
            while( (n = rio_readline(&rio[idx], res + clen, sizeof(res), &st)) > 0)
            {
                if(st < 0)
                {
                    cout << "dump cache : " << res  << endl;
                    int len = clen + n - 1;
                    rio[idx].cache = (char *) malloc (len);
                    rio[idx].cache_len = len;
                    memcpy(rio[idx].cache, res, len);
                    break;
                }
                cout << n <<" : " << res << endl; 
                cout << "write :" << sendn(fd, res, n + clen) << endl;
                clen = 0;
            }

            ev[0].events = events[i].events | EPOLLIN;
            ev[0].data.fd = fd;
            epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev[0]);

            if(n < 0)
            {
               cout << "readline error " << endl;
               return 0;
            }
            if(n == 0)
            {
                cout << "read fin" << endl;
                return 0;
            }
            
        }
    }
}
 
int main(int argc, char *argv[])
{
    rio_t rio[2];
    char res[10000];
    
 
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(1025);
    
    //test_block_cache(server_address);
    test_noblock_cache(server_address);
}
