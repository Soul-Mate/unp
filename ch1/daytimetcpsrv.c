#include "unp.h"
#include "unp_wsock.h"
#include <time.h>

int main(int argc, const char *argv[])
{
	int sockfd,confd;
	char buf[1024];
	time_t ticks;
	struct sockaddr_in srvaddr;
	
	sockfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&srvaddr,sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(9999);

	Bind(sockfd,(struct sockaddr *)&srvaddr,sizeof(srvaddr));

	Listen(sockfd,128);

	for(;;) {
		confd = Accept(sockfd,(struct sockaddr *)NULL,NULL);
		ticks = time(NULL);
		snprintf(buf,sizeof(buf),"%.24s\r\n",ctime(&ticks));
		write(confd,buf,strlen(buf));
		close(confd);
	}
}