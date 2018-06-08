#include"../headers/requestStruct.h"

char logedIn[255]="parham";

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
    struct request * response;
    response=req.send();
    free(response);
    return 0;

}
int login(char * username,char * password){
    struct request req(logedIn,$"login");
    pair usernamePair($"username",username);
    pair passwordPair($"password",password);
    req.addValue(usernamePair);
    req.addValue(passwordPair);
    struct request * response;
    response=req.send();
    if (strcmp((*response).values[0].value,"1")==0){
        strcpy(logedIn,username);
        return 1;
    }
    return 0;
    free(response);
}
void logout(){
    strcpy(logedIn,"-1");
}
int goTo(char chatId[10]){
    struct request req(logedIn,$"goto");
    pair chatIdPair($"chatid",chatId);
    struct request *  response;
    response=req.send();

    free(response);
    return 0;
}
int sendMsg(char chatId[20],char msg[10000]){
    struct request req(logedIn,$"sendmsg");
    pair chatIdPair($"chatid",chatId);
    pair msgPair($"msg",msg);
    req.addValue(chatIdPair);
    req.addValue(msgPair);
    struct request * response;
    response=req.send();
    free(response);
    return 0;
}
int leave(char chatId[20]){
    struct request req(logedIn,$"leave");
    pair chatIdPair($"chatid",chatId);
    req.addValue(chatIdPair);
    struct request * response;
    response=req.send();
    free(response);
    return 0;
}
int newChat(char username[255]){
    struct request req(logedIn,$"newchat");
    pair usernamePair($"username",username);
    req.addValue(usernamePair);
    struct request * response;
    response=req.send();

    free(response);
    return 0;
}
int newGp(char gpName[255]){
    struct request req(logedIn,$"newgp");
    pair namePair($"name",gpName);
    req.addValue(namePair);
    struct request * response;
    response=req.send();

    free(response);
    return 0;
}
int newchannel(char channelName[255]){
    struct request req(logedIn,$"newchannel");
    pair namePair($"name",channelName);
    req.addValue(namePair);
    struct request * response;
    response=req.send();
    free(response);
    return 0;
}
int showContacts(){
    struct request req(logedIn,$"showcontacts");
    struct request * response;
    response=req.send();

    free(response);
    return 0;
}
int main()
{
    
    return 0;
}

