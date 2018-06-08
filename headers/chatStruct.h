#include "../headers/userStruct.h"
int usernameToId(char * username);
void addToLastChatId();
int getLastChatId();
struct message{
    int id;
    char content[10000];
    char userName[255];
    int chatId;
};
struct chatInfo{
    int id;
    char type[20];
    char name[255];
    int admins[100];
    int adminNumbers;
    char chatMessagesLoc[255];
    char chatInfoLoc[255];
    chatInfo(bool flag=false){
        if (!flag){
            return;
        }
        adminNumbers=0;
        addToLastChatId();
        id=getLastChatId();
        strcpy(chatMessagesLoc,"../db/users/");
        char temp[10];
        sprintf(temp,"%d",id);
        strcat(chatMessagesLoc,temp);
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
