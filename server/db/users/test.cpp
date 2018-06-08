#include "stdio.h"
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
};
int main()
{
    struct user user;
    FILE * file;
    file=fopen("1/user.bin","r");
    fread(&user,sizeof(struct user),1,file);
    printf("%s  %s",user.username,user.password);
    fclose(file);
    return 0;
}
