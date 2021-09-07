#include <stdio.h>

struct Hash{
    char letter;
    int count;
}Stats[26];

void intialize();
void countletters(FILE *f);

int main(){
    intialize();


   FILE *f=NULL;
    char *location = "\\Users\\chris\\Desktop\\random.txt";
    f = fopen(location,"r+");
    if(f!=NULL){
       intialize();
       countletters(f);
       for(int i=0;i<26;i++){
           printf("Count of letter %c is %d\n",Stats[i].letter,Stats[i].count);
       }
    }
    else{
        printf("Rip");
    }
    fclose(f);
    f=NULL;

    return 0;
}

void intialize(){
    int a =97;
    for(int i=0;i<26;i++){
        struct Hash *pHash = &Stats[i];
        pHash->letter= (char) a;
        a++;
    }
}

void countletters(FILE *f){
    int read;
    while( (read = fgetc(f)) != EOF){
//        printf("%c",(int)read);
        if(97<=read&&read<=122){
         Stats[read-97].count++;
        }
    }
}

