import sys
##MatrixChain
##입력: 연속된 행렬 A1xA2x⋯xAn, 단, A1은 d0xd1, A2는 d1xd2, ⋯, An은 dn-1xdn이다.
##출력: 입력의 행렬 곱셈에 필요한 원소의 최소 곱셈 횟수 C[1,n]
##1. for i = 1 to n 
##2.         C[i,i] = 0 
##3. for L = 1 to n-1 { // L은 부분 문제의 크기를 조절하는 인덱스이다.
##4.       for i = 1 to n-L {
##5.              j = i + L
##6.             C[i,j] = ∞
##7.             for k = i to j-1 {
##8.                     temp = C[i,k] + C[k+1,j] + di-1dkdj
##9.                     if (temp < C[i,j])
##10.                             C[i,j] = temp 
##                          }
##                   }
##      }
##11. return C[1,n]

def matrixChain(dList):
    # dList = (d0, d1, d2,.....dn)   ; n개의 연속된 행렬의 행수와 열수의 리스트.
    n = len(dList) - 1
    C=[]
    for i in range(n+1):
        C.append([])
        for j in range(n+1):
            C[i].append(0)
    print_Matrix (C)
    for l in range(1,n):
        for i in range(1,n+1-l):
            j=i+l
            C[i][j]=sys.maxsize
            for k in range(i,j):
                temp = C[i][k] + C[k+1][j] + dList[i-1]*dList[k]*dList[j]
                if(temp<C[i][j]):
                    C[i][j]=temp
    print_Matrix(C)
    #TODOTodo
    #TODOTODO
    #TODOTODO
    #TODOTODO
    #TODOTODO
    #TODOTODO
    #TODOTODO
    
    return C[1][n]

def print_Matrix(M):
    print('------%dx%d--------'%(len(M), len(M[0])))
    for row in M :
        for col in row:
            print  ("%5d"%col, end=' ')
        print()
    print('-------------------')
    
if __name__=='__main__' :
    dL = (10, 20, 5, 15, 30)   # 10x20 , 20x5, ...
    c = matrixChain(dL)
    print ("필요한 곱셉횟수 : ", c)
    
