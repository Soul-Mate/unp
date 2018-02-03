#include "unp.h"
#include "unp_wsock.h"

int Socket(int domain, int type, int protocol)
{
	int fd;
	if ((fd = socket(domain,type,protocol)) == -1) {
		err_sys("socket error: %s\n",strerror(errno));
	}
	return fd;
}

void Bind(int sockfd,const struct sockaddr *addr, socklen_t addrlen)
{
	if (bind(sockfd,addr,addrlen) == -1) {
		err_sys("bind error: %s\n",strerror(errno));
	}
}

void Listen(int sockfd, int backlog)
{
	if (listen(sockfd, backlog) == -1) {
		err_sys("listen error: %s\n",strerror(errno));
	}
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int fd;
	if((fd = accept(sockfd, addr, addrlen)) == -1) {
		err_sys("accept error: %s\n",strerror(errno));
	}
	return fd;
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	if (connect(sockfd,addr,addrlen) == -1) {
		err_sys("connect error: %s\n",strerror(errno));
	}
}