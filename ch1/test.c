#include "unp.h"
#include "unp_wsock.h"
int main(void)
{
	int fd;
	fd = Socket(AF_INET,SOCK_STREAM,NULL);
    printf("%d\n", fd);
    return 0;
}