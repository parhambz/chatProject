#include "../../headers/chatStruct.h"
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
struct user getUserInfo(int userId){
    char * loc=getUserLoc(userId);
    FILE * file;
    file=fopen(loc,"r");
    struct user user;
    fread(&user,sizeof(struct user),1,file);
    fclose(file);
    free(loc);
    return user;
}
int getLastUserId(){
    int lastUserId;
    FILE * lastFP;
    lastFP=fopen("../db/users/lastid.bin","r");
    fread(&lastUserId,sizeof(int),1,lastFP);
    fclose(lastFP);
    return lastUserId;
}
void addToLastUserId(){
    FILE * lastFP;
    int id=getLastUserId()+1;
    lastFP=fopen("../db/users/lastid.bin","w");
    fwrite(&id,sizeof(int),1,lastFP);
    fclose(lastFP);
}
int usernameToId(char username[255]){
    int users=getLastUserId();
    for (int i=0;i<users;i++){
        struct user user=getUserInfo(i);
        if(strcmp(user.username,username)==0 ){
            return user.id;
        }
    } 
    return -1;   
}
struct request login(struct request req){
    struct request response($"server",$"login");
    int users=getLastUserId();
    pair resPair($"res",$"false");
    response.addValue(resPair);
    for (int i=0;i<(users+1);i++){
        //printf("%d",i);
        struct user user=getUserInfo(i);
        //printf("aa");
        if(strcmp(user.username,req.getValue($"username"))==0 && strcmp(user.password,req.getValue($"password"))==0){
            response.changeValue($"res",$"true");
            char sUserId[20];
            sprintf(sUserId,"%d",i);
            pair userIdPair($"userid",sUserId);
            response.addValue(userIdPair);
            return response;
        }
    }
    return response;
}
struct request  addUser(struct request  req){
    struct user user(true);
    user.setInfo(req.getValue($"firstname"),req.getValue($"lastname"),req.getValue($"username"),req.getValue($"password"));
    char * saveLoc =user.userInfoLoc;
    FILE * userFile;
    userFile=fopen(saveLoc,"w");
    fwrite(&user,sizeof(struct user),1,userFile);
    fclose(userFile);
    struct request response($"server",$"adduser");
    char temp[10];
    sprintf(temp,"%d",user.id);
    pair userIdPair($ "userid",temp);
    response.addValue(userIdPair);
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
    user=getUserInfo(id);
    user.addChat(chat.id);

    id=usernameToId(req.username);
    user=getUserInfo(id);
    user.addChat(chat.id);

    chat.addAdmin(req.getValue($"username"));
    chat.addAdmin(req.username);
    FILE * file;
    file=fopen(chat.chatMessagesLoc,"w");
    fclose(file);
    file=fopen(chat.chatInfoLoc,"w");
    fwrite(&chat,sizeof(struct chatInfo),1,file);
    fclose(file);
    struct request response($"server",$"newchat");
    char chatIdS[20];
    sprintf(chatIdS,"%d",chat.id);
    pair chatIdPair($"chatid",chatIdS);
    response.addValue(chatIdPair);
    return response;
}
struct request newGp(struct request req){
    struct chatInfo chat(true);
    strcpy(chat.name,req.getValue($"name"));
    strcpy(chat.type,"group");
    struct user user;
    int id=usernameToId(req.username);
    user=getUserInfo(id);
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
    pair chatIdPair($"chatid",chatIdS);
    response.addValue(chatIdPair);
    return response;   
}
struct request newChannel(struct request req){
    struct chatInfo chat(true);
    strcpy(chat.name,req.getValue($"name"));
    strcpy(chat.type,"chat");
    struct user user;
    int id=usernameToId(req.username);
    user=getUserInfo(id);
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
    pair chatIdPair($"chatid",chatIdS);
    response.addValue(chatIdPair);
    return response;
}
char * chatInfoLoc(int chatId){
    char * saveLoc;
    saveLoc=(char *)malloc(sizeof(char)*100);
    strcpy(saveLoc,"../db/chats/");
    char temp[10];
    sprintf(temp,"%d",chatId);
    strcat(saveLoc,temp);
    strcat(saveLoc,"/info.bin");
    return saveLoc;
}
struct chatInfo getChatStruct(int chatId){
    struct chatInfo chat;
    FILE * file;
    file=fopen(chatInfoLoc(chatId),"r");
    fread(&chat,sizeof(struct chatInfo),1,file);
    return chat;
}
struct message * getLast10 (int chatId){
    struct message * res;
    res=(struct message *)malloc(sizeof(struct message)*10+1);
    FILE * file;
    struct chatInfo chatInfo;
    chatInfo=getChatStruct(chatId);
    file=fopen(chatInfo.chatMessagesLoc,"r");

    for (int i=0; i<10;i++){
        fseek(file,sizeof(struct message)*i*(-1),SEEK_END);
        fread(&(res[i]),sizeof(struct message),1,file);
    }
    return res;
}
struct request Fgoto(struct request req){
    int userId=usernameToId(req.username);
    struct user user;
    user= getUserInfo(userId);
    int chatId=usernameToId(req.getValue($"chatid"));
    struct request response($"server",$"goto");
    for (int i=0 ;i<user.chatsNumber;i++){
        if (user.chats[i]==chatId){
            pair res($"res",$"true");
            struct message * msgs=getLast10(chatId);
            char temp[6000];
            for (int j=0 ;j<10;j++){
                struct message tempMsg=*(msgs+sizeof(struct message)*j);
                strcpy(temp,tempMsg.userName);
                strcat(temp,"/");
                char msgId[10];
                sprintf(msgId,"%d",tempMsg.id);
                strcat(temp,msgId);
                strcat(temp," :\n");
                strcat(temp,tempMsg.content);
                char pairName[255];
                sprintf(pairName,"%d",j);
                pair p(pairName,temp);
                response.addValue(p);
            }
            free(msgs);
        }
    }
    pair res ($"res",$"false");
    return response;
}
struct request getChatLists(struct request req){
    struct request response;
    int id=usernameToId(req.username);
    struct user user=getUserInfo(id);
    char res[4000];
    for(int i =0 ;i<user.chatsNumber;i++){
        strcat(res,"\n");
        char chatId[10];
        sprintf(chatId,"%d",user.chats[i]);
        strcat(res,chatId);
        strcat(res," --> ");
        struct chatInfo chat=getChatStruct(user.chats[i]);
        strcat(res,chat.name);
    }
    pair chatList($"chatlist",res);
    response.addValue(chatList);
    return response;

}
struct request sendMsg(struct request req){
    struct request response($"server",$"sendmsg");
    int userId= usernameToId(req.username);
    struct user user=getUserInfo(userId);
    int chatId=atoi(req.getValue($"chatid"));
    pair res($"res",$"false");
    for (int i=0;i<user.chatsNumber;i++){
        if(user.chats[i]==chatId){
            struct chatInfo chat=getChatStruct(chatId);
            if(strcmp(chat.type,"chat")==0||strcmp(chat.type,"group")==0){
                struct message msg;
                msg.id=chat.lastMessageId+1;
                msg.chatId=atoi(req.getValue($"chatid"));
                strcpy(msg.content,req.getValue($"content"));
                strcpy(msg.userName,req.username);
                msg.save();
                strcpy(res.value,"true");
                chat.lastMessageId++;
            }
            else if(strcmp(chat.type,"channel")==0 && strcmp(chat.type,"group")==0){
                struct message msg;
                msg.id=chat.lastMessageId+1;
                msg.chatId=atoi(req.getValue($"chatid"));
                strcpy(msg.content,req.getValue($"content"));
                strcpy(msg.userName,req.username);
                msg.save();
                strcpy(res.value,"true");
                chat.lastMessageId++;
            }
        }
    }
    response.addValue(res);
    return response;
}
struct request search(struct request req){
    int lastUserId=getLastUserId();
    char name[255];
    strcpy(name,req.getValue($"name"));
    struct request response($"server",$"search");
    pair res($"res",$"false");
    for (int i=0 ;i<lastUserId;i++){
        struct user user =getUserInfo(i);
        if (strcmp(name,user.firstname)==0){
            strcpy(res.value,"true");
            pair detail($"detail",user.firstname);
            strcat(detail.value," ");
            strcat(detail.value,user.lastname);
            strcat(detail.value,": ");
            strcat(detail.value,user.username);
            response.addValue(detail);
        }
    }
    response.addValue(res);
    return response;
}
struct request  requestHandle(struct request req){
    struct request response($"server",$"commandhandle");
    if (strcmp(req.command,"login")==0){
        return  login(req);
    }
    else if (strcmp(req.command,"adduser")==0)
    {
        return addUser(req);
    }
    else if (strcmp(req.command,"newchat")==0)
    {
        return newChat(req);
    }
    else if (strcmp(req.command,"newgp")==0)
    {
        return newGp(req);
    }
    else if (strcmp(req.command,"newchannel")==0)
    {
        return newChannel(req);
    }
    else if (strcmp(req.command,"goto")==0)
    {
        return Fgoto(req);
    }
    else if (strcmp(req.command,"search")==0)
    {
        return search(req);
    }
    return response;
}
int main()
{
    
    struct sockaddr_in address;
    char buff[bufferSize] ; 
    int fd,new_socket,valread;
    struct sockaddr_in server; 
    int in;
    
    char *data = (char*) malloc(sizeof(struct request));
    memset(data,0,sizeof(struct request));
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
    valread=read(new_socket,data,sizeof(struct request));
    struct request* req = (struct request*)data;
    //printf("\nRec data: %s\n",(*req).values[2].value);
    struct request response=requestHandle(*req);
    send(new_socket,&response,sizeof(struct request),0);

    return 0;
}

