/* logger.c - UDP server to echo packets */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define LOGGER_PORT 26211

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len = sizeof(cliaddr);
	char pre[64];
	char msg[1024];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(LOGGER_PORT);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	for (;;)
	{
		n = recvfrom(sockfd,msg,1000,0,(struct sockaddr *)&cliaddr,&len);
		if (n <= 0) {
			perror("logger: recvfrom failed");
			continue;
		}
		sprintf(pre, "%lld\t%s\t",
			(long long)time(0), inet_ntoa(cliaddr.sin_addr));

		write(1, pre, strlen(pre));
		msg[n] = '\n';
		write(1, msg, n + 1);
		fsync(1);
	}
}
