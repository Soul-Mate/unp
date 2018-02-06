#include "unp.h"
#include "unp_wunix.h"
#include "unp_wsock.h"

static int clients[FD_SETSIZE];

static fd_set all_set;

static int bind_and_listen();

/* 设置信号,用来回收退出的子进程 */
static void set_signal();

/* 接收请求 */
static void accept_request(int);

/* 向对端回射 */
static void server_echo(int, int);

void signal_child(int sig)
{
    int status;
    if (sig == SIGCHLD) {
        wait(&status);
    }
}

int main(int argc, const char *argv[])
{
    int i, listen_fd;
    listen_fd = bind_and_listen();
    /* 初始化存放对端连接的数组 */
    for (i = 0; i < FD_SETSIZE; i++) {
        clients[i] = -1;
    }
    set_signal();
    
    FD_ZERO(&all_set);
    FD_SET(listen_fd,&all_set);
    
    accept_request(listen_fd);
}

static int bind_and_listen()
{
    int sock_fd;
    struct sockaddr_in server_address;
    sock_fd = Socket(AF_INET,SOCK_STREAM,0);
    bzero(&server_address,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5002);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    
    Bind(sock_fd,(SA *)&server_address,sizeof(server_address));
    Listen(sock_fd,128);
    return sock_fd;
}

static void accept_request(int listen_fd)
{
    socklen_t cli_len;
    int i, max_i, ready_num, conn_fd, max_fd;
    struct sockaddr_in cli_address;
    
    /* 当前最大文件描述符 */
    max_fd = listen_fd;
    max_i = -1;
    for (;;) {
        ready_num = Select(max_fd + 1, &all_set, NULL, NULL, NULL);
        
        /* 新客户端连接 */
        if (FD_ISSET(listen_fd, &all_set)) {
            cli_len = sizeof(cli_address);
            conn_fd = Accept(listen_fd, (SA *)&cli_address, &cli_len);
        
            for (i = 0; i < FD_SETSIZE; i++) {
                if (clients[i] == -1) {
                    clients[i] = conn_fd;
                    FD_SET(conn_fd,&all_set);
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                err_quit("connect clients too many");
            }
            
            if (i > max_i) {
                max_i = i;
            }
            
            max_fd = conn_fd;
            
            if(--ready_num <= 0) {
                continue;
            }
            
        }
        for (i = 0; i <= max_i; i++) {
            if (clients[i]< 0) {
                continue;
            }
            server_echo(clients[i],i);
            if (--ready_num <= 0) {
                break;
            }
        }
    }
}

static void server_echo(int conn_fd, int index)
{
    ssize_t read_n;
    char buf[MAXLINE];
    read_n = Read(conn_fd,buf,MAXLINE);
    if (read_n == 0) {
        Close(conn_fd);
        clients[index] = -1;
        FD_CLR(conn_fd,&all_set);
        return;
    }
    Writen(conn_fd,buf,strlen(buf));
}

static void set_signal()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = signal_child;
    sigaction(SIGCHLD,&sa,NULL);
}