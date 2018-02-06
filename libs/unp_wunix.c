//
// Created by xyc on 18-2-6.
//
#include "unp.h"
#include "unp_wunix.h"

void Close(int fd)
{
    if (close(fd) < 0) {
        err_sys("close error: %s\n",strerror(errno));
    }
}


ssize_t Read(int fd, char *buf, size_t len)
{
    ssize_t read_n;
    if ((read_n = read(fd,buf,len)) < 0) {
        err_sys("read error: %s\n",strerror(errno));
    }
    return read_n;
}