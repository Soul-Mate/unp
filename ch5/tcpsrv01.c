#include "unp.h"
#include "unp_wsock.h"

static void echo(int fd);

void sig_child(int signo)
{
    if (signo == SIGCHLD) {
        int status;
        wait(&status);
        
    }
}

int main(int argc, const char *argv[])
{
    int sockfd,confd;
    struct sigaction sa;
    struct sockaddr_in srvaddr;
    
    /* init socket */
    sockfd = Socket(AF_INET,SOCK_STREAM,0);
    
    /* init server address */
    bzero(&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    srvaddr.sin_port = htons(5001);
    
    /* init signal */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sig_child;
    
    sigaction(SIGCHLD,&sa,NULL);
    
    Bind(sockfd,(SA *)&srvaddr, sizeof(srvaddr));
    
    Listen(sockfd,128);
    
    for (;;) {
        confd = Accept(sockfd,NULL,NULL);
        
        if (fork() == 0) {
            echo(confd);
            close(sockfd);
            exit(0);
        }
        close(confd);
    }
    
}


static void echo(int fd)
{
    ssize_t read_n;
    char buf[MAXLINE];
Again:
    while((read_n = read(fd,buf,MAXLINE)) > 0) {
        Writen(fd,buf,(size_t)read_n);
    }
    
    if (read_n < 0 && errno == EINTR) {
        goto Again;
        
    } else if(read_n < 0){
        err_sys("read error: %s\n", strerror(errno));
    }
    
    return;
}