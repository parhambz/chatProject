#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "../headers/requestStruct.h"
int port=8888;
int bufferSize=1024;

int main()
{
    struct sockaddr_in address;
    char buff[bufferSize] ; 
    int fd,new_socket,valread;
    struct sockaddr_in server; 
    int in;
    struct request req;

    memset(buff, '0',sizeof(buff));
    memset(&server, '0', sizeof(server)); 
	fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd<0){
        printf("fd socket nashod ");
    }
    server.sin_family = AF_INET;
	server.sin_port = htons(port); 
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(fd, (struct sockaddr*)&server, sizeof(server)); 
    listen(fd, 5);
    new_socket=accept(fd, (struct sockaddr*)NULL, NULL);
    //valread = read( new_socket , buff, sizeof(buff));
    //printf("%s",buff);
    valread=read(new_socket,&req,sizeof(struct request));
    printf("%s\n",req.values[0].value);
    return 0;
}

