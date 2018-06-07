struct user{
    int id;
    char firstname[255];
    char lastname[255];
    char username[255];
    char password[255];
    void setInfo(char ifirstname[255],char ilastname[255],char iusername[255],char ipassword[255]){
        strcpy(firstname,ifirstname);
        strcpy(lastname,ilastname);
        strcpy(username,iusername);
        strcpy(password,ipassword);
    }
};