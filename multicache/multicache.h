#include <iostream>
#include <set>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <functional>

namespace cache
{
std::set<std::string> first_cache;
std::set<std::string> second_cache;

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

bool process(const std::string &msg)
{
    //first cache, msg is processing
    pthread_mutex_lock(&first_mutex);
    if (1 == first_cache.count(msg))
    {
        std :: cout << "cacahe1 : " << first_cache.size() <<" omit" << msg << std :: endl;
        pthread_mutex_unlock(&first_mutex);

        return true; 
    }
    else
    {
        first_cache.insert(msg);
        pthread_mutex_unlock(&first_mutex);
    }

    //msgÊÇÎ¨Ò»µÄ£¬ÅÐ¶Ï¸ÃmsgÊÊÇ·ñ ÒÑ¾­´¦
    pthread_mutex_lock(&second_mutex);

    if(1 == second_cache.count(msg))
    {
        std :: cout << "cache2 : "<< second_cache.size() <<" has been alarm " << msg << std :: endl;
        pthread_mutex_unlock(&second_mutex);
        
        //free lock first, mysql update IO
        //make sure mysql IO is processed without lock
        usleep(20);
        
        pthread_mutex_lock(&first_mutex);
        first_cache.erase(msg);
        pthread_mutex_unlock(&first_mutex);
    }
    else
    {
        second_cache.insert(msg);
        pthread_mutex_unlock(&second_mutex);

        //free lock first, then mysql insert IO. 
        usleep(100); 

        //mysql IO end, free first cache.
        pthread_mutex_lock(&first_mutex);
        first_cache.erase(msg);
        pthread_mutex_unlock(&first_mutex);
    }
    return true; 
}
}
