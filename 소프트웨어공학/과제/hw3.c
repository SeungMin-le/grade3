#include<stdio.h>
#include<string.h>

#define N 100

int main(){

    char arr[N];
    int depth=0,count=0;

    gets(arr);

    for(int i=0;arr[i]!='\0';i++){
        if(arr[i]=='('){
            count++;

        }
        else if(arr[i]==')')
            count--;
        if(depth<count){
            depth=count;
        }
    }
    printf("%d",depth);

}
