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



int main(int argc, char *argv[])
{
    rio_t rio;
    char res[10000];
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(1025);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (sockaddr *) &server_address, sizeof(server_address));
    listen(listenfd, 10);
    
    //sleep(5);
    int confd = accept(listenfd, NULL, 0);
    
    //rio_init(&rio, confd, 5);
    //rio.rio_ptr = (char *) malloc(sizeof(char) * 5);
    
    //int n = rio_readn(&rio, res, 3);   
    //for(int i = 0; i < n; i++)
    //    printf("%c", res[i]);
    int n;
    char c;

    /* 
    while( (n = read(confd, &c, 1)) > 0)
    { 
        if(n == 0)
            printf("end\n");
        else
            printf("%c\n", c);
    }
    */
    

    //printf("%s\n", strerror(errno));
    //printf("%d\n", errno);

    char tmp[] = "haha\n";
    int i = 0;
    while(true)
    {
        n = write(confd, tmp, sizeof(tmp));
        printf("write =  %d %d %d\n", n, sizeof(tmp), i++);
    }
    //close(confd);
    printf("step over\n");
    //n = sendn(confd, tmp, sizeof(tmp));
    //printf("write =  %d %d\n", n, sizeof(tmp));

    //sendn(confd, tmp, sizeof(tmp));
}
