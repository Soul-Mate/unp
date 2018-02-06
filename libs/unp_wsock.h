#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#ifndef PROJECT_UNP_WSOCK_H
#define PROJECT_UNP_WSOCK_H

#ifndef SA
#define SA struct sockaddr
#endif

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

const char * Inet_ntop(int family, const void *addrptr);

void Inet_pton(int family, const char *src, void *dst);
#endif /* PROJECT_UNP_WSOCK_H */