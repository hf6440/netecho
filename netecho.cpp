#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int reply(int fd)
{
	char line[100];
	int readSize=0;
	while(true)
	{
		if((readSize=read(fd,line,99))==0)
			return 0;
		write(fd,line,readSize);	
	}
}
int main(int argc,char ** argv)
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(9877);
	bind(listenfd,(sockaddr *)&servaddr,sizeof(servaddr));
	listen(listenfd,1024);
	while(true)
	{

		clilen=sizeof(cliaddr);
		connfd=accept(listenfd,(sockaddr *)&cliaddr,&clilen);
		if((childpid=fork())==0)
		{
			close(listenfd);
			reply(connfd);
			exit(0);
		}
		close(connfd);
	}
	
	return 0;
}

