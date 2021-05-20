
def dpcoinchange(n, dList):
##DPCoinChange(n, [d1, d2, ⋯ ,dk ])
##입력: 거스름돈 n원, k개의 동전의 액면, d1> d2> ⋯ > dk=1 
##출력: C[n]
##
##1. for i = 1 to n C[i]=∞
##2. C[0]=0
##3. for j = 1 to n { // j는 1원부터 증가하는 (임시) 거스름돈 액수이고, j=n이면 입력에 주어진 거스름돈이 된다.
##4.       for i = 1 to k {
##5.             if (di ≤ j) and (C[j-di]+1<C[j])
##6.                      C[j]=C[j-di]+1
##            }
##    }
##7. return C[n]

    k = len(dList)
    C = []
    for i in range(n+1):
        C.append(float('inf'))
    C[0]=0
    
    for j in range(n+1):
        for i in range(k):
            if dList[i]<= j and (C[j-dList[i]]+1<C[j]):
                C[j]=C[j-dList[i]]+1
    print(C)
            
    return C[n]

if __name__ == '__main__' :
    n = 20
    dList = [16, 10, 5, 1]
    total_coin = dpcoinchange(n, dList)
    print ("The number of coins=", total_coin)
