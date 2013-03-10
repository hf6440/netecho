#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <fcntl.h>
int main(int argc,char ** argv)
{
	int clifd;
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	clifd=socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(9877);	
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	connect(clifd,(sockaddr *)&servaddr,sizeof(servaddr));
	char line[20]="this is a word\0";
	write(clifd,line,20);
//	printf("%s",line);
	close(clifd);

	return 0;
}

