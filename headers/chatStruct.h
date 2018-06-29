#include "../headers/userStruct.h"
int usernameToId(char * username);
void addToLastChatId();
int getLastChatId();
struct chatInfo getChatStruct(int chatId);

struct chatInfo{
    int id;
    char type[20];
    char name[255];
    int admins[100];
    int adminNumbers;
    int lastMessageId;
    char chatMessagesLoc[255];
    char chatInfoLoc[255];
    chatInfo(bool flag=false){
        if (!flag){
            return;
        }
        lastMessageId=0;
        adminNumbers=0;
        addToLastChatId();
        id=getLastChatId();
        strcpy(chatMessagesLoc,"../db/users/");
        char temp[10];
        sprintf(temp,"%d",id);
        strcat(chatMessagesLoc,temp);
        //create the directory
        mkdir(chatMessagesLoc, 0700);
        strcat(chatMessagesLoc,"msg.bin");
        strcpy(chatInfoLoc,"../db/users/");
        strcat(chatInfoLoc,temp);
        strcat(chatInfoLoc,"info.bin");
    }
    void addAdmin(char username[255]){
        int id =usernameToId(username);
        admins[adminNumbers]=id;
        adminNumbers++;
    }
};
struct message{
    int id;
    char content[5000];
    char userName[255];
    int chatId;
    void save(){
        struct chatInfo chat =getChatStruct(chatId);
        FILE * file;
        file=fopen(chat.chatMessagesLoc,"a");
        fseek(file,chat.lastMessageId*sizeof(struct message),SEEK_SET);
        fwrite(this,sizeof(struct message),1,file);
        fclose(file);
        file=fopen(chat.chatInfoLoc,"w");
        fwrite(&chat,sizeof(struct chatInfo),1,file);
        
    }
};