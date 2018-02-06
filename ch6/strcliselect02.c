#include "unp.h"
#include "unp_wsock.h"
#include "unp_wunix.h"


static char *addr;

static void str_cli(int);

int main(int argc, char *argv[])
{
    if (argc != 2 ) {
        err_quit("Usage: please input server <address>");
    }
    
        int sockfd;
        struct sockaddr_in srv_addr;
        sockfd = Socket(AF_INET,SOCK_STREAM,0);
        
        bzero(&srv_addr,sizeof(srv_addr));
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_port = htons(5002);
        Inet_pton(AF_INET,argv[1],&srv_addr.sin_addr);
        
        Connect(sockfd,(SA *)&srv_addr, sizeof(srv_addr));
        str_cli(sockfd);
        return 0;
}


static void str_cli(int sockfd)
{
    int fd,max_fd;
    fd_set all_set;
    char send_buf[MAXLINE];
    char receive_buf[MAXLINE];
    FD_ZERO(&all_set);
    fd = fileno(stdin);
    for (;;) {
        FD_SET(fd,&all_set);
        FD_SET(sockfd,&all_set);
        max_fd = max(sockfd,fd);
        
        Select(max_fd + 1,&all_set,NULL,NULL,NULL);
        
        if (FD_ISSET(sockfd,&all_set)) {
            if (Readline(sockfd,receive_buf,MAXLINE)== 0) {
                err_quit("str_cli: server terminated prematurely");
            }
            fputs(receive_buf,stdout);
        }
        
        if (FD_ISSET(fd,&all_set)) {
            while (Read(fd,send_buf,MAXLINE) == 0){
                
                return;
            }
            Writen(sockfd,send_buf,strlen(send_buf));
        }
    }
}