#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include"../headers/requestStruct.h"
int port =8888;
char serverIp[]="127.0.0.1";
char logedIn[255]="parham";


int sendReq(void * msg,int size){
    struct sockaddr_in server; 
    int fd = 0;
    //char buff[1024];
    //memset(buff, '0',sizeof(buff));
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

    return 0;
}
int newContact(char * firtsName,char * lastname,char * username){
    struct request req;
    strcpy(req.command,"newcontact");
    strcpy(req.username,logedIn);
    //char value[500];
    /*strcpy(value,username);
    strcat(value,"~");
    strcat(value,name);
    strcpy(req.value,value);
    sendReq(&req,sizeof(struct request));*/
    pair namePair($"name",firtsName);
    pair usernamePair($"username",username);
    req.addValue(namePair);
    req.addValue(usernamePair);
    sendReq(&req,sizeof(struct request));
    return 0;

}
int login(char * username,char * password){

    return 0;
}
int main()
{
    newContact($"mamad",$"mamadian",$"m");
    return 0;
}

