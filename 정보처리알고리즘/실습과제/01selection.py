from random import randint
import timeit

def pivotSplit(A,left,p,right):

    A[p],A[left]=A[left],A[p]
    i=left+1
    j=right
    while(i<=j):
        while(i<=j and A[i] <= A[left]):
            i=i+1
        while(i<=j and A[j] >= A[left]):
            j=j-1
        if(i<j):
            A[i],A[j]=A[j],A[i]
            i=i+1
            j=j-1
    new_p=i-1
    A[left],A[new_p]=A[new_p],A[left]
    return new_p

def selection(A,left,right,k):
    p=randint(left,right)
    p=pivotSplit(A,left,p,right)

    S=p-left

    if k<=S:
        return selection(A,left,p-1,k)
    elif k==S+1:
        return A[p]
    else:
        return selection(A,p+1,right,k-S-1)
