//
// Created by xyc on 18-2-2.
//
#include "unp.h"

char *read_buf_ptr;
char read_buf[MAXLINE];

static ssize_t read_count;

static int read_to_buf(int fd, char *ptr);

static int readline(int fd, void *ptr, size_t max_len);


static int read_to_buf(int fd, char *ptr)
{
    if (read_count <= 0) {
    Again:
        /* read in buf */
        if ((read_count = read(fd,read_buf,sizeof(read_buf))) < 0) {
            
            /* if interrupt */
            if (errno == EINTR) {
                goto Again;
            }
            
            return -1;
        }
        
        /* read null or EOF */
        if (read_count == 0) {
            return 0;
            
        }
        read_buf_ptr = read_buf;
    }
    
    /* from the read buf take a character   */
    read_count--;
    *ptr = *read_buf_ptr++;
    return 1;
}

static int readline(int fd, void *any, size_t max_len)
{
    int i;
    int read_count;
    char c;
    char *read_ptr;
    
    read_ptr = (char *)any;
    
    for (i = 0; i < max_len; i++) {
        
        if ((read_count = read_to_buf(fd,&c)) == 1) {
            *read_ptr++ = c;
            
            if (c == '\n'){
                break;
            }
            
        } else if(read_count == 0) {
            *read_ptr = 0;
            return (i - 1);
            
        } else {
            return -1;
        }
    }
    *read_ptr = 0;
    return i;
}

ssize_t Readline(int fd, void *any, size_t max_len)
{
    ssize_t n;
    if ((n = readline(fd,any,max_len)) < 0) {
        err_sys("read line error");
        
    }
    return n;
}