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

rio_t rio;
char res[10000];
//测试 阻塞，按照行读写，每次发生一整行
void test_block_sequenceLine(struct sockaddr_in client_address)
{
    int fd0 = socket(AF_INET, SOCK_STREAM, 0);
    int n;
    connect(fd0, (sockaddr *)&client_address, sizeof(client_address));

    int fd1 = socket(AF_INET, SOCK_STREAM, 0);
    
    n = connect(fd1, (sockaddr *)&client_address, sizeof(client_address));

    if(n < 0)
        printf("connect error \n");
    char tmp1[] = "12345";
    char tmp2[] = "678\n";

      
    n = sendn(fd0, tmp1, sizeof(tmp1)-1);
    //printf("fd0 : %d\n", n);
    n = sendn(fd1, tmp1, sizeof(tmp1)-1);
    //printf("fd1 : %d\n", n);
    sleep(1);
    
    n = sendn(fd0, tmp2, sizeof(tmp2)-1);
    n = sendn(fd1, tmp2, sizeof(tmp2)-1);
    
    n = sendn(fd0, tmp1, sizeof(tmp1)-1);
    n = sendn(fd1, tmp1, sizeof(tmp1)-1);
    
    sleep(1);
    n = read(fd0, res, 1000);
    res[n] = '\0';
    cout << "first recv: " << res << endl;
    n = read(fd1, res, 1000);
    res[n] = '\0';
    cout << "first recv: " << res << endl;
    
    n = sendn(fd0, tmp2, sizeof(tmp2)-1);
    n = sendn(fd1, tmp2, sizeof(tmp2)-1);
    
    sleep(1);
    n = read(fd0, res, 1000);
    res[n] = '\0';
    cout << "second recv: " << res << endl;
    n = read(fd1, res, 1000);
    res[n] = '\0';
    cout << "second recv: " << res << endl;
     
}


//测试 阻塞，按照行读写，每次发送不足一行
//测试 非阻塞，一次 发伤屯 多行， 如果对面 用了cache 读的话，看看能否正常处理
void test_block_cutLine(struct sockaddr_in client_address)
{
    int fd0 = socket(AF_INET, SOCK_STREAM, 0);
    int n;
    net_connect_to_ms(fd0, (sockaddr *) &client_address, 
                      sizeof(client_address), 2000);

    int fd1 = socket(AF_INET, SOCK_STREAM, 0);
    
    n = net_connect_to_ms(fd1, (sockaddr *) &client_address, 
                          sizeof(client_address), 2000);
   
    if(n < 0)
        printf("connect error \n");
    
    //不足一行
    //char tmp1[] = "12345";
    //char tmp2[] = "678\n";
    
    //发送多行
    char tmp1[] = "1\n2\n3\n45";
    char tmp2[] = "678\n";
      
    n = sendn(fd0, tmp1, sizeof(tmp1)-1);
    //n = sendn(fd0, tmp1, sizeof(tmp1)-1);
    //printf("fd0 : %d\n", n);
    n = sendn(fd1, tmp1, sizeof(tmp1)-1);
    //printf("fd1 : %d\n", n);
    sleep(1);
    
    n = sendn(fd0, tmp2, sizeof(tmp2)-1);
    n = sendn(fd1, tmp2, sizeof(tmp2)-1);
    
    n = sendn(fd0, tmp1, sizeof(tmp1)-1);
    n = sendn(fd1, tmp1, sizeof(tmp1)-1);
    
    sleep(1);
    n = read(fd0, res, 1000);
    res[n] = '\0';
    cout << "first recv: " << res << endl;
    n = read(fd1, res, 1000);
    res[n] = '\0';
    cout << "first recv: " << res << endl;
    
    n = sendn(fd0, tmp2, sizeof(tmp2)-1);
    n = sendn(fd1, tmp2, sizeof(tmp2)-1);
    
    sleep(1);
    n = read(fd0, res, 1000);
    res[n] = '\0';
    cout << "second recv: " << res << endl;
    n = read(fd1, res, 1000);
    res[n] = '\0';
    cout << "second recv: " << res << endl;
     
}

int main(int argc, char *argv[])
{
    
    struct sockaddr_in client_address;
    char addr[] = "127.0.0.1";
    set_tcp_sockaddr(addr, 1025, &client_address);
    
    //test_block_sequenceLine(client_address);
    test_block_cutLine(client_address);
}
