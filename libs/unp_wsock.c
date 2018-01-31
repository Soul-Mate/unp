#include "unp.h"
#include "unp_wsock.h"

int Socket(int domain, int type, int protocol)
{
	int fd;
	if ((fd = socket(domain,type,protocol)) == -1) {
		err_quit("socket error: %s\n",strerror(errno));
	}
	return fd;
}

int Bind(int sockfd,const struct sockaddr *addr, socklen_t addrlen)
{
	if (bind(sockfd,addr,addrlen) == -1) {
		err_quit("bind error: %s\n",strerror(errno));
	}
	return 0;
}

int Listen(int sockfd, int backlog)
{
	if (listen(sockfd, backlog) == -1) {
		err_quit("listen error: %s\n",strerror(errno));
	}
	return 0;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int fd;
	if((fd = accept(sockfd, addr, addrlen)) == -1) {
		err_quit("accept error: %s\n",strerror(errno));
	}
	return fd;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	if (connect(sockfd,addr,addrlen) == -1) {
		err_quit("connect error: %s\n",strerror(errno));
	}
	return 0;
}