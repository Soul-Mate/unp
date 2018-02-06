#include "unp.h"
#include "unp_wsock.h"


int main(int argc, const char *argv[])
{
    socklen_t clilen;
    ssize_t read_n;
    int listenfd,connfd,sockfd,maxfd,nready;
    int i,maxi,clients[FD_SETSIZE];
    struct sockaddr_in servaddr, cliaddr;
    char buf[MAXLINE];
    fd_set allset,rset;
    
    listenfd = Socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5002);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));
    Listen(listenfd,128);
    
    maxi = -1;
    maxfd = listenfd;
    for (i = 0; i < FD_SETSIZE; i++) {
        clients[i] = -1;
    }
    
    FD_ZERO(&allset);
    FD_SET(listenfd,&allset);
    
    for (;;) {
        rset = allset;
        nready = Select(maxfd + 1,&rset, NULL, NULL, NULL);
        
        if (FD_ISSET(listenfd, &rset)) {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd,(SA *)&cliaddr,&clilen);
            printf("new client: %s, port %d\n",
                   Inet_ntop(AF_INET, &cliaddr.sin_addr),
                   ntohs(cliaddr.sin_port));
            for (i = 0; i < FD_SETSIZE; i++) {
                if (clients[i] < 0) {
                    clients[i] = connfd;
                    FD_SET(connfd,&allset);
                    break;
                }
            }
            
            if (i == FD_SETSIZE) {
                err_quit("connect client is limited");
            }
            
            if (i > maxi) {
                maxi = i;
            }
            
            if (connfd > maxfd) {
                maxfd = connfd;
            }
            
            if (--nready <= 0) {
                continue;
            }
        }
        
        for (i = 0; i <= maxi; i++) {
            if (clients[i] < 0) {
                continue;
            }
            sockfd = clients[i];
            if (FD_ISSET(sockfd, &rset)) {
                read_n = read(sockfd, buf, MAXLINE);
                if (read_n == 0) {
                    close(sockfd);
                    FD_CLR(sockfd,&allset);
                    clients[i] = -1;
                }
                Writen(sockfd, buf, strlen(buf));
                
                if (--nready <= 0) {
                    break;
                }
            }
        }
    }
    return 0;
}