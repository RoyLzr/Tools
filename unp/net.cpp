#include "net.h"

void rio_init(rio_t *rp, int fd, int len)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_len = len;
    rp->rio_bufptr = rp->rio_ptr;
    rp->cache = NULL;
    rp->cache_len = 0;
}

static ssize_t
rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;
    while(rp->rio_cnt <= 0)
    {
        rp->rio_cnt = read(rp->rio_fd, rp->rio_ptr, rp->rio_len);
        if(rp->rio_cnt == 0)
            return 0;
        else if(rp->rio_cnt < 0)
        {
            if(errno != EINTR)
                return -1;
        } 
        else
            rp->rio_bufptr = rp->rio_ptr;      
    }
    if(rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    else
        cnt = n;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;  
    return cnt;
}


ssize_t 
rio_readn(rio_t *rp, void *usrbuf, size_t n, int * st)
{
    int nleft = n;
    int nread = 0;
    char * buf = (char *)usrbuf;
    *st = 1;
    while(nleft > 0)
    {
        nread = rio_read(rp, buf, nleft);
        if(nread == 0)
            break;
        else if(nread < 0)
        {
            if(errno == EAGAIN)
            {
                *st = -1;
                break;
            }
            if(errno != EINTR)
                return -1;
            nread = 0;
        }
        nleft -= nread;
        buf += nread;
    }
    return n - nleft;
}

ssize_t
rio_readline(rio_t *rp, void *usrbuf, size_t maxlen, int * st)
{
    char c, *buf = (char *)usrbuf;
    int i;
    int nread;
    *st = 1;

    for(i = 1; i < maxlen; i++)
    {
        nread = rio_read(rp, &c, 1);
        if(nread == 0)
        {
            if(i == 1)
                return 0;
            else
                break;
        }
        else if(nread < 0)
        {
            if(errno == EAGAIN)
            { 
                *st = -1;   
                break;
            }
            else
                return -1;
        }
        else
        {
            *buf = c;
            buf++;
            if(c == '\n')
                break;
        }     
    }
    *buf = '\0';
    return i;
}

ssize_t 
readn_to_ms(int fd, void *ptr, size_t nbytes, int msecs)
{
    struct timeval tv;
    struct timeval old_tv;
    ssize_t nread;
    int sockflag;
    int ret;
    int timeuse = 0;
    socklen_t oplen = (socklen_t) sizeof (tv);
    
    nread = recv(fd, ptr, nbytes, MSG_DONTWAIT);
    
    if(nread == nbytes)
        return nread;
    if(nread == 0)
        return 0;
    if((nread<0) && (errno!=EAGAIN) && (errno!=EINTR))
        return -1;
    if (nread < 0) 
    {
        nread = 0;
    }

    if (0 == msecs) 
    {
        errno = ETIMEDOUT;
        return -1;
    }
    if (msecs < 0) {
       msecs = INT_MAX; 
    }

    if(getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &old_tv, &oplen) < 0)
        return -1;
    if((sockflag = fcntl(fd, F_GETFL, 0)) < 0)
        return -1;

    if (sockflag&O_NONBLOCK) 
    {
        if(fcntl(fd, F_SETFL, (sockflag)&(~O_NONBLOCK)) < 0)
            return -1;
    }

    struct timeval cur;
    struct timeval last;
    do 
    {
        tv.tv_sec = msecs/1000;
        tv.tv_usec = (msecs % 1000) * 1000;
        if(setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, oplen) < 0)
            return -1;
        gettimeofday(&cur, NULL);
        
        do 
        {
            ret = recv(fd, (char*)ptr + nread, nbytes - (size_t)nread, MSG_WAITALL); 
        } while (ret < 0 && errno == EINTR);
        
        if (ret < 0 && EAGAIN==errno) 
        {
            //没数据，超时了
            errno = ETIMEDOUT;
        }
        
        if (ret > 0 && nread + ret != (ssize_t) nbytes) 
        {
            gettimeofday(&last, NULL);
            //判断是不是真的超时了
            timeuse = ((last.tv_usec - cur.tv_usec)/1000 + (last.tv_sec - cur.tv_sec) * 1000);
            if (timeuse >= msecs) 
            {
                //真超时了
                errno = ETIMEDOUT;
                ret = -1;
                nread = -1;
            } 
            else 
            {
                //被中断了？继续读
                nread += ret;
            }
        }  
        else if (ret < 0) 
        {
            nread = -1;
        } 
        else 
        {
            nread += ret;
        }
      //没写完，继续
    } while (ret > 0 && nbytes != (size_t)nread);

    if (sockflag & O_NONBLOCK) 
    {
        if(fcntl(fd, F_SETFL, sockflag) < 0)
            return -1;
    }
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &old_tv, oplen)<0 )
        return -1;

    return nread;
}

ssize_t 
rio_readn_to_ms(rio_t *rp, void *usrbuf, size_t n, int msecs)
{
    int nleft = n;
    int nread = 0;
    int sockflag;
    char * buf = (char *)usrbuf;

    if(sockflag = fcntl(rp->rio_fd, F_GETFL, 0) < 0)
        return -1;
    set_fd_noblock(rp->rio_fd);
    
    struct timeval tv;
    tv.tv_sec = msecs/1000;
    tv.tv_usec = (msecs % 1000) * 1000; 
 
    while(nleft > 0)
    {
        nread = rio_read(rp, buf, nleft);
        if(nread == 0)
            break;
        else if(nread < 0)
        {
            if(errno == EAGAIN)
            {
               fd_set rset;
               FD_ZERO(&rset);
               FD_SET(rp->rio_fd, &rset);
               if(select(rp->rio_fd + 1, &rset, NULL, NULL, &tv) <= 0)
               {
                    errno = ETIMEDOUT;
                    n = nleft - 1;
                    break;
               }   
               else
                   continue; 
            }
            if(errno != EINTR)
                return -1;
            nread = 0;
        }
        nleft -= nread;
        buf += nread;
    }
    if(fcntl(rp->rio_fd, F_SETFL, sockflag) < 0)
        return -1;

    return n - nleft;
}

ssize_t
rio_readline_to_ms(rio_t *rp, void *usrbuf, size_t maxlen, int msecs)
{
    char c, *buf = (char *)usrbuf;
    int i;
    int nread;
    int sockflag;
    
    struct timeval tv;
    tv.tv_sec = msecs/1000;
    tv.tv_usec = (msecs % 1000) * 1000;  

    if(sockflag = fcntl(rp->rio_fd, F_GETFL, 0) < 0)
        return -1;
    set_fd_noblock(rp->rio_fd);

    for(i = 1; i < maxlen; i++)
    {
        nread = rio_read(rp, &c, 1);
        if(nread == 0)
        {
            if(i == 1)
                return 0;
            else
                break;
        }
        else if(nread < 0)
        {
            if(errno == EAGAIN)
            { 
               fd_set rset;
               FD_ZERO(&rset);
               FD_SET(rp->rio_fd, &rset);
               if(select(rp->rio_fd + 1, &rset, NULL, NULL, &tv) <= 0)
               {
                    errno = ETIMEDOUT;
                    i = - 1;
                    break;
               }   
               else
                   continue; 
            }
            else
                return -1;
        }
        else
        {
            *buf = c;
            buf++;
            if(c == '\n')
                break;
        }     
    }
    *buf = '\0';
    if(fcntl(rp->rio_fd, F_SETFL, sockflag) < 0)
        return -1;
    return i;
}

ssize_t
sendn(int fd, void *usrbuf, size_t n)
{
    int nleft = n;
    int nwrite = 0;
    char * buf = (char *)usrbuf;
    while(nleft > 0)
    {
        nwrite = write(fd, buf, nleft);
        if(nwrite < 0)
        {
            if(errno != EINTR)
                return -1;
            nwrite = 0;
        }
        else if(nwrite == 0)
            break;
        buf += nwrite;
        nleft -= nwrite;
    }
    return n - nleft;
}


int 
set_fd(int fd, int flags, int closed)
{
    int val;
    if ( (val = fcntl(fd, F_GETFL, 0)) < 0)
    {
        if(closed == 0)
        {
            close(fd);
        }
        return -1;
    }
    val |= flags;
    if ( (fcntl(fd, F_SETFL, val)) < 0)
    {
        if(closed == 0)
            close(fd);
        return -1;
    }
    return 0;
}

int 
set_fd_noblock(int fd)
{
   return set_fd(fd, O_NONBLOCK, 1);
}


/*
ssize_t 
writen_to_ms(int sock, const void *ptr, size_t nbytes, int msecs)
{
    struct timeval tv;
    struct timeval old_tv;
    ssize_t nwrite = 0;
    int ret = 0;
    int sockflag = 0;
    int timeuse = 0;
    socklen_t oplen = sizeof(tv);

    nwrite = send(sock, ptr, nbytes, MSG_DONTWAIT);
    UL_RETURN_VAL_IF((nwrite==(ssize_t)nbytes), nwrite);
    UL_RETURN_VAL_IF((nwrite<0)&&(errno!=EAGAIN)&&(errno!=EWOULDBLOCK)&&(errno!=EINTR), -1);
    if (nwrite < 0) {
        nwrite = 0;
    }

    //0的时候不希望会被堵塞住
    if (0 == msecs) {
        errno = ETIMEDOUT;
        return -1;
    }
    //负数的时候我们要堵塞
    if (msecs < 0) {
       msecs = INT_MAX; 
    }

    UL_RETURN_VAL_IF(getsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &old_tv, &oplen)<0, -1);
    UL_RETURN_VAL_IF((sockflag = fcntl(sock, F_GETFL, 0))<0, -1);
    if (sockflag&O_NONBLOCK) {
        UL_RETURN_VAL_IF(fcntl(sock, F_SETFL, (sockflag)&(~O_NONBLOCK))<0, -1);
    }
    oplen = sizeof(tv);
    struct timeval cur;
    struct timeval last;
    do {
        tv.tv_sec = msecs/1000;
        tv.tv_usec = (msecs%1000)*1000;
        //set都已经失败了,对sock的其它操作已经没有多大意义了
        gettimeofday(&cur, NULL);
        UL_RETURN_VAL_IF(setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, oplen)<0, -1); 
        do { 
            ret = send(sock, (char*)ptr + nwrite, nbytes-(size_t)nwrite, MSG_WAITALL); 
        } while (ret < 0 && EINTR == errno);

        if (ret > 0 && nwrite+ret < (ssize_t)nbytes) {
            //判断是否真是超时
            gettimeofday(&last, NULL);
            timeuse = ((last.tv_usec - cur.tv_usec)/1000+(last.tv_sec - cur.tv_sec)*1000);
            if (timeuse >= msecs) {
                //真的超时了
                errno = ETIMEDOUT;
                ret = -1;
                nwrite = -1;
            } else {
                //不是超时，一般是被中断了, 继续写
                msecs -= timeuse;
                nwrite += ret;

            }
        } else if (ret < 0) {
            nwrite = -1;
        } else {
            nwrite += ret;
        }
        //没搞定继续写
    } while (ret > 0 && nbytes != (size_t)nwrite);
    if (sockflag & O_NONBLOCK) {
        UL_RETURN_VAL_IF(fcntl(sock, F_SETFL, sockflag)<0, -1);
    }
    UL_RETURN_VAL_IF(setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &old_tv, oplen)<0, -1);
    
    return nwrite;
}
*/
