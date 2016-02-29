#include "../lib/unp.h"

int main(int argc,char **argv){
	int sockfd,n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in serveraddr;

	if(argc != 2){
		// err_quit("usage: a.out <IPAddress>");
		printf("usage: a.out <IPAddress>");
		exit(1);
	}

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
		// err_sys("socket error");
		printf("socket error");
		exit(1);
	}

	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(13);
	if (inet_pton(AF_INET,argv[1],&serveraddr.sin_addr)<=0){
		// err_quit("inet_pton error for %s",argv[1]);
		printf("inet_pton error for %s",argv[1]);
		exit(1);
	}

	if (connect(sockfd,(SA *)&serveraddr,sizeof(serveraddr))<0)	
	{
		// err_sys("connect error");
		printf("connect error");
		exit(1);
	}

	while ((n = read(sockfd,recvline,MAXLINE))>0){
		recvline[n]=0;
		if (fputs(recvline,stdout)==EOF)
		{
			// err_sys("fputs error");
			printf("fputs error");
			exit(1);
		}
	}
	if (n<0){
		// err_sys("read error");
		printf("read error");
		exit(1);
	}

	exit(0);
}