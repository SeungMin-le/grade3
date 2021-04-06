#include<stdio.h>
#define N 100

int main(){

    char arr[N];
    int count=1;
    gets(arr);

    for(int i=0;arr[i]!='\0';i++){
        if(arr[i]==' ')
            count++;
    }
    printf("%d",count);

    return 0;
}
