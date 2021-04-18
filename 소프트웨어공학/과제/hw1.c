#include<stdio.h>
#define N 2000
int main(){
    int num, arr[N];
    int max,min;
    scanf("%d",&num);
    for(int i=0;i<num;i++){
        scanf("%d",arr+i);
    }

    max= arr[0];
    min= arr[0];
    for(int i=1;i<num;i++){
        if(max<arr[i])
            max=arr[i];
        if(min>arr[i])
            min=arr[i];
    }
    printf("%d %d",max,min);

    return 0;

}
