#define $ (char*)

typedef struct Pair{
    char key [255];
    char value [255];

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

    request() {
        size = 0;
    }
    void addValue(pair p){
        values[size]=p;
        size++;
    }
};
