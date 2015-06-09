#include "net.h"

void rio_init(rio_t *rp, int fd, int len)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_len = len;
    rp->rio_bufptr = rp->rio_ptr;
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
rio_readn(rio_t *rp, void *usrbuf, size_t n)
{
    int nleft = n;
    int nread = 0;
    char * buf = (char *)usrbuf;
    while(nleft > 0)
    {
        nread = rio_read(rp, buf, nleft);
        if(nread == 0)
            break;
        else if(nread < 0)
        {
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
rio_readline(rio_t *rp, void *usrbuf, size_t maxlen)
{
    char c, *buf = (char *)usrbuf;
    int i;
    int nread;
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
            return -1;
        else
        {
            *buf = c;
            buf++;
            if(c == '\n')
                break;
        }     
    }
    *buf = 0;
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
        if(nwrite <= 0)
        {
            if(errno != EINTR)
                return -1;
            nwrite = 0;
        }
        buf += nwrite;
        nleft -= nwrite;
    }
    return n;
}


