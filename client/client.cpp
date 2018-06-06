#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int port =8888;
char serverIp[]="127.0.0.1";

struct request{
    char username[255];
    char command[255];
    char value[500];

};

int sendReq(void * msg,int size){
    struct sockaddr_in server; 
    int fd = 0;
    char buff[1024];
    memset(buff, '0',sizeof(buff));
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd<0){
        printf("fd socket nashod !");
    }
	memset(&server, '0', sizeof(server)); 
    server.sin_family = AF_INET;
	server.sin_port =  htons(port);
    int in = inet_pton(AF_INET,serverIp, &server.sin_addr);
    if (in<0){
        printf("invalid ip");
    }
    in= connect(fd,(struct sockaddr *)&server,sizeof(struct sockaddr));
    if (in <0){
        printf("connect nashod !");
    }
    send (fd,msg,size,0);
    close(fd);
}

int main()
{
  
    return 0;
}

