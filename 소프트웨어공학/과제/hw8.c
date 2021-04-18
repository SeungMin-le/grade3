#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define STR_NUM 200
#define MAX_SIZE 20
int cmpr(void *a,void *b){
    return (strcmp(*(char**)a,*(char**)b));
}

int input_str(char **arr){
    char str[STR_NUM];
    char *tk;
    int size;

    gets(str);

    tk=strtok(str," ");
    arr[0]=_strdup(tk);
    size=1;
    while(1){
            tk=strtok(NULL," ");
            if(tk==NULL)
                break;
            arr[size++]=_strdup(tk);

    }
    return size;


}

int main(){
    char **arr;
    int size;
    int i;
    int count[MAX_SIZE];


    arr=(char**)malloc(sizeof(char*)*MAX_SIZE);
    size=input_str(arr);

    qsort(arr,size,sizeof(arr[0]),cmpr);

    for(i=0;i<MAX_SIZE;i++){
        count[i]=1;
    }
    for(i=0;i<size-1;i++){
        if(strcmp(arr[i],arr[i+1])==0)
            count[i+1]=count[i]+count[i+1];

        else
            printf("%s %d\n",arr[i],count[i]);
    }
    printf("%s %d",arr[size-1],count[size-1]);


}
