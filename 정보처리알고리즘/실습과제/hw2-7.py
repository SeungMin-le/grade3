import random

def binarySearch(a_list,n):
    sortList=sorted(a_list)
    print(sortList)
    i=0
    s_i=0
    e_i=len(sortList)
    
    while i < len(sortList):
        mid=int((s_i+e_i)/2)
  
        if n==sortList[mid]:
            return mid;
        elif n<sortList[mid]:
            e_i=mid
        elif n>sortList[mid]:
            s_i=mid
        i= i+1
    return -1

if __name__=='__main__':
    arr = [random.randint(0,100)]
    i=1
    n=random.randint(0,100)
    while i < 10:
        arr.append(random.randint(0,100))
        i=i+1
    print("search num is " , n)
    result=binarySearch(arr,n)
    
    if result == -1:
        print("not here")
    else:  
        print("search location is ", result+1)
    
