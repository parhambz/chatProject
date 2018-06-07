#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "../headers/requestStruct.h"
#include "../headers/userStruct.h"
int port=8888;
int bufferSize=1024;

int getLastUserId(){
    int lastUserId;
    FILE * lastFP;
    lastFP=fopen("../db/users/lastid.bin","r");
    fread(&lastUserId,sizeof(int),1,lastFP);
    fclose(lastFP);
    return lastUserId;
}
struct request * addUser(struct request  req){
    struct user user;
    user.setInfo(req.getValue($"firstname"),req.getValue($"lastname"),req.getValue($"username"),req.getValue($"password"));
    int lastUserId=getLastUserId();
    lastUserId++;
    user.id=lastUserId;
    FILE * lastFP;
    lastFP=fopen("../db/users/lastid.bin","w");
    fwrite(&lastUserId,sizeof(int),1,lastFP);
    fclose(lastFP);
    char saveLoc[500];
    strcpy(saveLoc,"../db/users/");
    char temp[10];
    sprintf(temp,"%d",lastUserId);
    strcat(saveLoc,temp);
    strcat(saveLoc,"/user.bin");
    FILE * userFile;
    userFile=fopen(saveLoc,"w");
    fwrite(&user,sizeof(struct user),1,userFile);
    fclose(userFile);
    struct request response("server","adduser");
    pair userIdPair($ "userid",temp);
    response.addValue(userIdPair);
    return &response;
}

struct request * requestHandle(struct request req){
    struct request * response;
    response=(struct request *)malloc(sizeof(struct request));
    
    return response;
}
int main()
{
    struct sockaddr_in address;
    char buff[bufferSize] ; 
    int fd,new_socket,valread;
    struct sockaddr_in server; 
    int in;
    struct request req($"",$"");

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
    struct request * response;
    response=requestHandle(req);
    send(new_socket,response,sizeof(struct request),0);
    free(response);
    return 0;
}

