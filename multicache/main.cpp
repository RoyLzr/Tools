#include "multicache.h"
#include <stdlib.h>
#include <stdio.h>
 
#define MAX 1000
void * run(void * arg)
{
    while(true)
    {
        int value = rand();
        char tmp[256];
        sprintf(tmp ,"%d", value);
        std::string s = tmp;
        cache :: process(s);
    }
    return NULL;
}

int main()
{
    for(int i = 0; i < MAX; i++)
    {
        pthread_t tid;
        if(pthread_create(&tid, NULL, run, NULL) !=0 )
        {
            return -1;
        }
        std:: cout << i << std::endl;
    }
    sleep(65535);
    return 0;
}
