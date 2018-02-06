#include "unp.h"
#include "unp_wsock.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		err_quit("Usage: <ip address>");
	}

	int sockfd,n;
	char buf[1024];
	struct sockaddr_in cliaddr;
	sockfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&cliaddr,sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(9999);
	inet_pton(AF_INET,argv[1],&cliaddr.sin_addr);
	
	Connect(sockfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr));

	while((n = read(sockfd,buf,1024)) > 0) {
		buf[n] = 0;
		if (fputs(buf,stdout) == EOF)
			err_quit("fputs error");
	}
}