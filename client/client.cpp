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
    pair chatIdPair("chatid",chatId);
    struct request * response;
    response=req.send();

    free(response);
}
int main()
{
    newContact($"mamad",$"mamadian",$"m");
    return 0;
}

