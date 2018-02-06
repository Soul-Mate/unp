#include "unp.h"
#include "unp_wsock.h"

static const char * ipaddr= "127.0.0.1";

static uint16_t port = 5002;

static void str_cli(int);

int main(int argc, const char *argv[])
{
    int sockfd;
    struct sockaddr_in srvaddr;
    sockfd = Socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&srvaddr,sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(port);
    Inet_pton(AF_INET,ipaddr,&srvaddr.sin_addr);
    
    Connect(sockfd,(SA *)&srvaddr, sizeof(srvaddr));
    str_cli(sockfd);
    return 0;
}

void str_cli(int sockfd)
{
    int fd;
    int maxfd;
    fd_set allset;
    char send_buf[MAXLINE];
    char receive_buf[MAXLINE];
    FD_ZERO(&allset);
    fd = fileno(stdin);
    for (;;) {
        FD_SET(fd,&allset);
        FD_SET(sockfd,&allset);
        maxfd = max(sockfd,fd);
        
        Select(maxfd + 1,&allset,NULL,NULL,NULL);
        
        if (FD_ISSET(sockfd,&allset)) {
            if (Readline(sockfd,receive_buf,MAXLINE)== 0) {
                err_quit("str_cli: server terminated prematurely");
            }
            fputs(receive_buf,stdout);
        }
        
        if (FD_ISSET(fd,&allset)) {
            while (fgets(send_buf,MAXLINE,stdin) == NULL){
                return;
            }
            Writen(sockfd,send_buf,strlen(send_buf));
            sleep(100);
        }
    }
}