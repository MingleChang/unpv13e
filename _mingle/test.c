#include "../lib/unp.h"

int main(int argc, const char * argv[]) {
    int sockfd,n;
    char recvline[MAXLINE+1];
    struct sockaddr_in servaddr;
    
    if (argc != 2) {
        printf("exit");
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        printf("socket error");
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(13);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0) {
        printf("inet_pton error");
    }
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        printf("connect error");
    }
    
    while ((n = read(sockfd, recvline, MAXLINE))>0) {
        recvline[n]=0;
        if (fputs(recvline, stdout)==EOF) {
            printf("fputs error");
        }
    }
    if (n<0) {
        printf("read error");
    }
    return 0;
}