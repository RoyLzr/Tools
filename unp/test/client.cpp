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
    
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(1025);
    inet_pton(AF_INET, "127.0.0.1", &client_address.sin_addr);
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    
    int n = connect(fd, (sockaddr *)&client_address, sizeof(client_address));

    if(n < 0)
        printf("connect error \n");
    char tmp[] = "12345";
    n = sendn(fd, tmp, sizeof(tmp));
    printf("%d\n", n);
    //close(fd);
   
    /* 
    char c = 'c';
    while(true)
    {
        n = write(fd, &c, 1);
        if(n == 0)
            printf("fin  %d", n);
        if(n > 0)
            printf("write  %d", n);
        if(n < 0)
        {
            printf("%s\n", strerror(errno));
        }
        sleep(1);
    }
    */
    
    sleep(1000);
}
