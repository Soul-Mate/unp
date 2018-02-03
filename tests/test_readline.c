//
// Created by xyc on 18-2-2.
//
#include "unp.h"

int main(int argc, const char *argv[])
{
    int fd;
    
    if ((fd = open("/home/xyc/code/c/unp/tests/test_file",O_RDONLY)) < 0) {
        err_sys("open error: %s",strerror(errno));
    }
    char buf[10];
    Readline(fd,buf,10);
    printf("%s\n",buf);
}