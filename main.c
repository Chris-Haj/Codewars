#include <stdio.h>
#include <stdbool.h>

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
       bool space = false;
       for(int i=0;i<26;i++){
           printf("Count of letter %c is %d",Stats[i].letter,Stats[i].count);
           if(space == false)
               printf("\t");
           else
               printf("\n");
           space = !space;
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

