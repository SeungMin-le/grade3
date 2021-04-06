#include<stdio.h>
#define N 2000
int main(){
    int count[N],arr[N];
    int num;

    scanf("%d",&num);

    for(int i=0;i<num;i++){
        scanf("%d",arr+i);
        printf("%d ",arr[i]);
        count[arr[i]%10]+=1;

    }
    printf("\n");
    for(int i=0;i<10;i++){
        printf("%d %d\n",i,count[i]);
    }


    return 0;
}
