def knapsack(C, n, W, V):
##Knapsack(C, n, W, V)
##입력: 배낭의 용량 C, n개의 물건과 각 물건 i의 무게 wi와 가치 vi, 단, i = 1, 2, ⋯, n 
##출력: K[n,C]
##1. for i = 0 to n   K[i,0]=0     // 배낭의 용량이 0일 때
##2. for w = 0 to C K[0,w]=0    // 물건 0이란 어떤 물건도 고려하지 않을 때
##3. for i = 1 to n {
##4.      for w = 1 to C {          // w는 배낭의 (임시) 용량
##5.                if ( wi > w )	 // 물건 i의 무게가 임시 배낭 용량을 초과하면
##6.                        K[i,w] = K[i-1,w]
##7.                else          // 물건 i를 배낭에 담지 않을 경우와 담을 경우 고려
##8.                        K[i,w] = max{K[i-1,w], K[i-1,w-wi]+vi}
##          }
##     }
##9. return K[n,C]
    
    K = []
    for i in range(0, n+1):
        K.append([0 for w in range(0, C+1)])
    K[0][0] = 0               
    for i in range(1, n+1):
        K[i][0] = 0
    for w in range(1, C+1):
        K[0][w] = 0

    ### TODO TODO         
    ### TODO TODO         
    ### TODO TODO         
    ### TODO TODO         
    ### TODO TODO         
    ### TODO TODO         
    ### TODO TODO         
    ### TODO TODO         
    ### TODO TODO         
    ### TODO TODO         

    print ("For Debugging...")
    print_matrix(K, n, C)
    print ()
    return K[n][C]


def print_matrix(K, n, C):
    for i in range(0, n+1):
        for w in range(0, C+1):
            print ("%3d"%(K[i][w]), end=' ')
        print ()

if __name__ == '__main__' :
    C = 10
    n = 4
    W = [None, 5, 4, 6, 3]
    V = [None, 10,40,30,50]
    total_v = knapsack(C, n, W, V)
    print ("Total Values=", total_v)
