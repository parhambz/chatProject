#include"../headers/requestStruct.h"

char logedIn[255]="";
int state=0;
char curChatId[20];

int addUser(char * firstname,char * lastname,char * username,char * password){
    struct request req(logedIn,$"adduser");
    pair firtsnamePair($"firstname",firstname);
    pair lastnamePair($"lastname",lastname);
    pair usernamePair($"username",username);
    pair passwordPair($"password",password);
    req.addValue(firtsnamePair);
    req.addValue(lastnamePair);
    req.addValue(usernamePair);
    req.addValue(passwordPair);
    struct request respone=req.send();
    printf("%s",respone.getValue($"userid"));
    return 0;
}
int newContact(char * firtsName,char * lastname,char * username){
    struct request req(logedIn,$"newcontact");

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
    struct request  response;
    response=req.send();
    return 0;

}
int login(char * username,char * password){
    struct request req(logedIn,$"login");
    pair usernamePair($"username",username);
    pair passwordPair($"password",password);
    req.addValue(usernamePair);
    req.addValue(passwordPair);
    struct request response;
    response=req.send();
    if (strcmp(response.getValue($"res"),"true")==0){
        strcpy(logedIn,username);
        return 1;
    }
    return 0;
    
}
void logout(){
    strcpy(logedIn,"-1");
}
int goTo(char chatId[10]){
    struct request req(logedIn,$"goto");
    pair chatIdPair($"chatid",chatId);
    struct request response;
    response=req.send();

    return 0;
}
int sendMsg(char chatId[20],char msg[10000]){
    struct request req(logedIn,$"sendmsg");
    pair chatIdPair($"chatid",chatId);
    pair msgPair($"content",msg);
    req.addValue(chatIdPair);
    req.addValue(msgPair);
    struct request response;
    response=req.send();
    return 0;
}
int leave(char chatId[20]){
    struct request req(logedIn,$"leave");
    pair chatIdPair($"chatid",chatId);
    req.addValue(chatIdPair);
    struct request response;
    response=req.send();
    return 0;
}
int newChat(char username[255]){
    struct request req(logedIn,$"newchat");
    pair usernamePair($"username",username);
    req.addValue(usernamePair);
    struct request response;
    response=req.send();

    return 0;
}
int newGp(char gpName[255]){
    struct request req(logedIn,$"newgp");
    pair namePair($"name",gpName);
    req.addValue(namePair);
    struct request response;
    response=req.send();

    return 0;
}
int newchannel(char channelName[255]){
    struct request req(logedIn,$"newchannel");
    pair namePair($"name",channelName);
    req.addValue(namePair);
    struct request response;
    response=req.send();
    return 0;
}
int showContacts(){
    struct request req(logedIn,$"showcontacts");
    struct request response;
    response=req.send();
    return 0;
}
int search (char name[255]){
    struct request req(logedIn,$"search");
    pair namePair ("name",name);
    req.addValue(namePair);
    struct request response;
    response=req.send();
    return 0;
}
void getLine(char line[]) {
    char c = 0;
    int i = 0;
    int flag=0;
    while (c != '\n') {
        c = getchar();
        if(c!=' '){
            flag=1;
        }
        if (flag==1){
        line[i] = c;
        i++;
        }
    }
    line[i - 1] = 0;
}
void getCommand(int start,char line [],char res[]){
    int len = strlen(line);
    for (int i=start ;i<len;i++){
        if(line[i]==' '){
            res[i-start]='\0';
            break;
        }else {
            res[i-start]=line[i];
        }
    }
}
void getMsg(char line[],char msg[]){
    int len = strlen(line);
    for(int i=8;i<len;i++){
        msg[i-8]=line[i];
    }

}
int menu(){
    printf("\n\n\n\n");
    switch(state){
        case 0:
            printf("login <username> <password>\n");
            printf("adduser <firstname> <lastname> <username> <password>\n");
            break;
        case 1:
            printf("newchat <username>\n");
            printf("newgp <gpname>\n");
            printf("newchannel <channelname>\n");
            printf("chatlist\n");
            printf("logout\n");
            break;
        case 2:
            printf("goto <chatid>\n");
            printf("main\n");
            break;
        case 3:
            printf ("sendmsg <msg content>");
            printf("main\n");
            break;
    }
    char line[6000];
    getLine(line);
    char command[6000];
    int start=0;
    getCommand(start,line,command);
    if(state==0){
        if (strcmp(command,"login")==0){
            start+=strlen(command);
            char username[255];
            getCommand(start,line,username);
            start+=strlen(username);
            char password[255];
            getCommand(start,line,password);
            int res=login(username,password);
            if (res==1){
                state=1;
                menu();
            }else{
                menu();
            }
        }else if(strcmp(command,"adduser")==0){
            start+=strlen(command);
            char firstname[255];
            getCommand(start,line,firstname);
            start+=strlen(firstname);

            char lastname[255];
            getCommand(start,line,lastname);
            start+=strlen(lastname);

            char username[255];
            getCommand(start,line,username);
            start+=strlen(username);

            char password[255];
            getCommand(start,line,password);
            int res=addUser(firstname,lastname,username,password);
            printf("user %d added!",res);
            menu();
        }
    }
    else if(state=1){
        if (strcmp(command,"newchat")==0){
            start+=strlen(command);
            char username[255];
            getCommand(start,line,username);
            int res=newChat(username);
            printf("chat %d added!",res);
            menu();
        }else if (strcmp(command,"newgp")==0){
            start+=strlen(command);
            char name[255];
            getCommand(start,line,name);
            int res=newGp(name);
            printf("chat %d added!",res);
            menu();
        }else if (strcmp(command,"newchannel")==0){
            start+=strlen(command);
            char name[255];
            getCommand(start,line,name);
            int res=newchannel(name);
            printf("chat %d added!",res);
            menu();
            }
        else if (strcmp(command,"logout")==0){
            printf("logged out!");
            strcpy(logedIn,"");
            state=0;
            menu();
        }

    }else if(state==2){
       if (strcmp(command,"goto")==0){
            start+=strlen(command);
            char chatId[255];
            getCommand(start,line,chatId);
            int res=goTo(chatId);
            strcpy(curChatId,chatId);
            menu();
            }else if(strcmp(command,"main")==0){
                state=1;
                menu();
            }
    }else if(state==3){
        if (strcmp(command,"sendmsg")==0){
            char msg[5000];
            getMsg(line,msg);
            sendMsg(curChatId,msg);
            state=1;
            menu();
        }else if(strcmp(command,"main")==0){
                state=1;
                menu();
            }
    }
    
}
int main()
{
    menu();

    return 0;
}