//
// Created by xyc on 18-2-2.
//

#include "unp.h"

static ssize_t readn(int fd,void *any,size_t n);

static ssize_t readn(int fd,void *any,size_t n)
{
    char *ptr;
    size_t nleft;
    ssize_t read_n;
    
    nleft = n;
    ptr = (char *)any;
    
    while (nleft > 0) {
        if((read_n = read(fd,ptr,nleft)) < 0) {
            
            /* if interrupt */
            if (errno == EINTR) {
                continue;
            } else {
                return -1;
            }
            
        /* read EOF */
        } else if(read_n == 0) {
            break;
            
        } else {
            nleft -= read_n;
            ptr += read_n;
        }
    }
    
    return (n - nleft);
}

ssize_t Readn(int fd, void *any, size_t n)
{
    ssize_t read_n;
    if ((read_n = readn(fd,any,n)) < 0) {
        err_sys("readn error");
    }
    
    return read_n;
}