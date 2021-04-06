#include<stdio.h>
#include<string.h>
#define N 20

int main(){

    char a[N],b[N];
    char newa[N],newb[N];
    char result[N]={NULL};
    gets(a);
    gets(b);
    for(int i=0;a[i]!='\0';i++){
        for(int j=0;b[j]!='\0';j++){
            for(int k=0;b[k]!='\0';k++){
                strncpy(newa,a+j,i);
                newa[i]='\0';
                strncpy(newb,b+k,i);
                newb[i]='\0';

                if(strcmp(newa,newb)==0 && strlen(newa)>strlen(result)){
                    strcpy(result,newa);

                }
            }
        }
    }
    printf("%s",result);
    return 0;

}
