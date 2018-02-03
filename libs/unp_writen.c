//
// Created by xyc on 18-2-2.
#include "unp.h"

static ssize_t writen(int fd, void *any, ssize_t n);

static ssize_t writen(int fd, void *any, ssize_t n)
{
    size_t nleft;
    ssize_t write_n;
    const char *ptr;

    nleft = n;
    ptr = (char *)any;
    
    while (nleft > 0) {
        if ((write_n = write(fd,any,nleft)) <= 0) {
            /* if interrupt */
            if (write_n < 0 && errno == EINTR) {
                write_n = 0;
                
            } else {
                return -1;
            }
        }
        nleft -= write_n;
        ptr += write_n;
    }
    return write_n;
}


ssize_t Writen(int fd, void *any, size_t n)
{
    ssize_t write_n;
    if ( (write_n = writen(fd,any,n)) < 0) {
        err_sys("writen error");
    }
    
    return write_n;
}