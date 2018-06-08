#include "../headers/requestStruct.h"
int getLastUserId();

struct user{
    int id;
    char firstname[255];
    char lastname[255];
    char username[255];
    char password[255];
    int chats [1000];
    int chatsNumber;
    char contactLoc[255];
    char userInfoLoc[255];
    user(bool flag=false){
        if (!flag){
            return;
        }
        
        int lastUserId=getLastUserId();
        lastUserId++;
        id=lastUserId;
        chatsNumber=0;
        strcpy(userInfoLoc,"../db/users/");
        char temp[10];
        sprintf(temp,"%d",id);
        strcat(userInfoLoc,temp);
        mkdir(userInfoLoc, 0700);
        strcat(userInfoLoc,"/user.bin");

        strcpy(contactLoc,"../db/users/");
        strcat(contactLoc,temp);
        strcat(contactLoc,"/contact.bin");
    }
    void addChat(int chatId){
        chats[chatsNumber]=chatId;
        chatsNumber++;
    }
    void setInfo(char ifirstname[255],char ilastname[255],char iusername[255],char ipassword[255]){
        strcpy(firstname,ifirstname);
        strcpy(lastname,ilastname);
        strcpy(username,iusername);
        strcpy(password,ipassword);
    }
};