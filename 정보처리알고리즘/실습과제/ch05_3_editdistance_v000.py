
def editDistance(S, T):
##입력: 스트링 S, T, 단, S와 T의 길이는 각각 m과 n이다.
##출력: S를 T로 변환하는 편집 거리, E[m,n]
##1. for i=0 to m E[i,0]=i    // 0번 열의 초기화
##2. for j=0 to n E[0,j]=j     // 0번 행의 초기화
##3. for i=1 to m
##4.     for j=1 to n
##5.          E[i,j] = min{E[i,j-1]+1, E[i-1,j]+1, E[i-1,j-1]+α}
##6. return E[m,n]
    E =  []
    m = len(S)
    n = len(T)
    for i in range(0, m+1):
        E.append([0 for j in range(0, n+1)])
    E[0][0]=0  
    for i in range(1, m+1):
        E[i][0] = i
    for j in range(1, n+1):
        E[0][j] = j
    for i in range(1,m+1):
        for j in range(1,n+1):
            if S[i-1] == T[j-1]:
                k=0
            else:
                k=1
            E[i][j]=min(E[i][j-1]+1,E[i-1][j]+1,E[i-1][j-1]+k)


    print ("For Debugging ....")
    print_matrix(E, m, n)
    print ()
    return E[m][n]

def print_matrix(E, m, n):
    for i in range(0, m+1):
        for j in range(0, n+1):
            print ("%3d"%(E[i][j]), end=' ')
        print ()


if __name__ == '__main__' :
    S = "stone"
    T = "strong"
    print ("S=", S)
    print ("T=", T)
    d = editDistance(S, T)
    print ("Total distance=", d)
    print ()
   
