import random

def mySearch(a_list,n):
    print(a_list)
    i=0
    while i < len(a_list):
        if a_list[i]==n:
            return i
        i=i+1
    return -1

if __name__=='__main__':
    i=1
    arr=[random.randint(0,100)]
    n=random.randint(0,100)
    print("search num is ",n)
    while i<10:
        arr.append(random.randint(0,100))
        i=i+1
    result = mySearch(arr,n)
    
    if result == -1:
        print("not here")
    else:
        print("search location is", result+1)
        
