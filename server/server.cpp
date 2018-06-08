#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "../headers/requestStruct.h"
#include "../headers/userStruct.h"
#include "../headers/chatStruct.h"
int port=8888;
int bufferSize=1024;

char * getUserLoc(int userId){
    char * saveLoc;
    saveLoc=(char *)malloc(sizeof(char)*100);
    strcpy(saveLoc,"../db/users/");
    char temp[10];
    sprintf(temp,"%d",userId);
    strcat(saveLoc,temp);
    strcat(saveLoc,"/user.bin");
    return saveLoc;
}
struct user getUser(int id){
    char * userLoc=getUserLoc(id);
    FILE * userFile;
    fopen(userLoc,"r");
    struct user user;
    fread(&user,sizeof(struct user),1,userFile);
    free(userLoc);
    fclose(userFile);
    return user;
}
int usernameToId(char username[255]){
    int users=getLastUserId();
    for (int i=0;i<users;i++){
        struct user user=getUser(i);
        if(strcmp(user.username,username)==0 ){
            return user.id;
        }
    }    
}
int getLastUserId(){
    int lastUserId;
    FILE * lastFP;
    lastFP=fopen("../db/users/lastid.bin","r");
    fread(&lastUserId,sizeof(int),1,lastFP);
    fclose(lastFP);
    return lastUserId;
}
struct request  login(struct request req){
    struct request response($"server",$"login");
    int users=getLastUserId();
    pair resPair($"res",$"false");
    response.addValue(resPair);
    for (int i=0;i<users;i++){
        struct user user=getUser(i);
        if(strcmp(user.username,req.getValue($"username"))==0 && strcmp(user.password,req.getValue($"password"))==0){
            response.changeValue($"res",$"true");
            char sUserId[20];
            sprintf(sUserId,"%d",i);
            pair userIdPair($"userid",sUserId);
            req.addValue(userIdPair);
        }
    }
    return response;
}
struct request  addUser(struct request  req){
    struct user user(true);
    user.setInfo(req.getValue($"firstname"),req.getValue($"lastname"),req.getValue($"username"),req.getValue($"password"));
    FILE * lastFP;
    lastFP=fopen("../db/users/lastid.bin","w");
    fwrite(&(user.id),sizeof(int),1,lastFP);
    fclose(lastFP);
    char * saveLoc =getUserLoc(user.id);
    FILE * userFile;
    userFile=fopen(saveLoc,"w");
    fwrite(&user,sizeof(struct user),1,userFile);
    fclose(userFile);
    struct request response("server","adduser");
    char temp[10];
    sprintf(temp,"%d",user.id);
    pair userIdPair($ "userid",temp);
    response.addValue(userIdPair);
    free(saveLoc);
    userFile=fopen(user.contactLoc,"w");
    fclose(userFile);
    return response;
}

int getLastChatId(){
    int lastChatId;
    FILE * lastFP;
    lastFP=fopen("../db/chats/lastid.bin","r");
    fread(&lastChatId,sizeof(int),1,lastFP);
    fclose(lastFP);
    return lastChatId;  
}

void addToLastChatId(){
    int lastChatId=getLastChatId();
    lastChatId++;
    FILE * lastFP;
    lastFP=fopen("../db/chats/lastid.bin","w");
    fwrite(&lastChatId,sizeof(int),1,lastFP);
    fclose(lastFP);
}
struct request newChat(struct request req){
    struct chatInfo chat(true);
    strcpy(chat.name,"");
    strcpy(chat.type,"chat");
    struct user user;
    int id=usernameToId(req.getValue($"username"));
    user=getUser(id);
    user.addChat(chat.id);

    int id=usernameToId(req.username);
    user=getUser(id);
    user.addChat(chat.id);

    chat.addAdmin(req.getValue($"username"));
    chat.addAdmin(req.username);
    FILE * file;
    file=fopen(chat.chatMessagesLoc,"W");
    fclose(file);
    file=fopen(chat.chatInfoLoc,"w");
    fwrite(&chat,sizeof(struct chatInfo),1,file);
    fclose(file);
    struct request response($"server",$"newchat");
    char chatIdS[20];
    sprintf(chatIdS,"%d",chat.id);
    pair chatIdPair("chatid",chatIdS);
    response.addValue(chatIdPair);
    return response;
}
struct request newGp(struct request req){
    struct chatInfo chat(true);
    strcpy(chat.name,req.getValue($"name"));
    strcpy(chat.type,"group");
    struct user user;
    int id=usernameToId(req.username);
    user=getUser(id);
    user.addChat(chat.id);



    chat.addAdmin(req.username);
    FILE * file;
    file=fopen(chat.chatMessagesLoc,"W");
    fclose(file);
    file=fopen(chat.chatInfoLoc,"w");
    fwrite(&chat,sizeof(struct chatInfo),1,file);
    fclose(file);
    struct request response($"server",$"newgp");
    char chatIdS[20];
    sprintf(chatIdS,"%d",chat.id);
    pair chatIdPair("chatid",chatIdS);
    response.addValue(chatIdPair);
    return response;   
}
struct request newChannel(struct request req){
    struct chatInfo chat(true);
    strcpy(chat.name,req.getValue("name"));
    strcpy(chat.type,"chat");
    struct user user;
    int id=usernameToId(req.username);
    user=getUser(id);
    user.addChat(chat.id);
    chat.addAdmin(req.getValue($"username"));
    chat.addAdmin(req.username);
    FILE * file;
    file=fopen(chat.chatMessagesLoc,"W");
    fclose(file);
    file=fopen(chat.chatInfoLoc,"w");
    fwrite(&chat,sizeof(struct chatInfo),1,file);
    fclose(file);
    struct request response($"server",$"newchat");
    char chatIdS[20];
    sprintf(chatIdS,"%d",chat.id);
    pair chatIdPair("chatid",chatIdS);
    response.addValue(chatIdPair);
    return response;
}
struct request  requestHandle(struct request req){
    if (strcmp(req.command,"login")==0){
        return  login(req);
    }
    else if (strcmp(req.command,"adduser")==0)
    {
        return addUser(req);
    }
    
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
    send(new_socket,& requestHandle(req),sizeof(struct request),0);

    return 0;
}

