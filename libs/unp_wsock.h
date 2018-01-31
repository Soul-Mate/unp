#include <sys/socket.h>
#include <arpa/inet.h>

#ifndef PROJECT_UNP_WSOCK_H
#define PROJECT_UNP_WSOCK_H

int Socket(int domain, int type, int protocol);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
#endif /* PROJECT_UNP_WSOCK_H */