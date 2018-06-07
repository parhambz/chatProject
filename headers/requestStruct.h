#define $ (char*)
struct request * sendReq(void * msg,int size){
    struct sockaddr_in server; 
    struct request * response;
    response=(struct request *)malloc(sizeof(struct request));
    int fd = 0;
    //char buff[1024];
    //memset(buff, '0',sizeof(buff));
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd<0){
        printf("fd socket nashod !");
    }
	memset(&server, '0', sizeof(server)); 
    server.sin_family = AF_INET;
	server.sin_port =  htons(port);
    int in = inet_pton(AF_INET,serverIp, &server.sin_addr);
    if (in<0){
        printf("invalid ip");
    }
    in= connect(fd,(struct sockaddr *)&server,sizeof(struct sockaddr));
    if (in <0){
        printf("connect nashod !");
    }
    send (fd,msg,size,0);
    read(fd,response,sizeof(struct request));
    close(fd);
    return response;
}
typedef struct Pair{
    char key [255];
    char value [10000];

    Pair(char ikey[255] ,char  ivalue[255]){
        strcpy(key,ikey);
        strcpy(value,ivalue);    
    }

    Pair() {}
    
} pair;
struct request{
    char username[255];
    char command[255];
    pair  values[20];
    int size;

    request(char iusername[255],char icommand[255]) {
        strcpy(username,iusername);
        strcpy(command,icommand);
        size = 0;
    }
    void addValue(pair p){
        values[size]=p;
        size++;
    }

    struct request * send(){
       return sendReq(this,sizeof(struct request));
    }
};
