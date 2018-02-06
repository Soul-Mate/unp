#include "unp.h"
#include "unp_wsock.h"

static const char *srvip = "127.0.0.1";

static void echo(int fd);

int main(int argc, const char *argv[])
{
    int sockfd;
    struct sockaddr_in cliaddr;
    
    /* init socket */
    sockfd = Socket(AF_INET,SOCK_STREAM,0);
    
    /* init client address */
    bzero(&cliaddr,sizeof (cliaddr));
    
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(5002);
    inet_pton(AF_INET,srvip,&cliaddr.sin_addr);
    
    Connect(sockfd,(struct sockaddr *)&cliaddr, sizeof(cliaddr));
   
    echo(sockfd);
}

static void echo(int fd)
{
    char send_buf[MAXLINE];
    char recv_buf[MAXLINE];
    
    while (fgets(send_buf,MAXLINE,stdin) != NULL) {
        Writen(fd,send_buf,strlen(send_buf));
        if (Readline(fd,recv_buf,MAXLINE) == 0) {
            err_sys("prematurely");
        }
        fputs(recv_buf,stdout);
    }
}