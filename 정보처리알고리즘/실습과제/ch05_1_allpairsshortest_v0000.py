from ch05_0_graphutils_v20 import *
import time
##AllPairsShortest
##입력: 2차원 배열 D, 단, D[i,j]=선분 (i,j)의 가중치,
##          만일 선분 (i,j)이 존재하지 않으면 D[i,j]=∞,
##          모든 i에 대하여 D[i,i]=0이다.
##출력: 모든 쌍 최단 경로의 거리를 저장한 2-d 배열 D
##
##1. for k = 1 to n
##2.     for i = 1 to n (단, i≠k)
##3.          for j = 1 to n (단, j≠k, j≠i)
##4.                D[i,j] = min { D[i,k]+D[k,j] ,  D[i,j] }

def allPairsShortest(D) :
    n = len(D)
    for k in range(n):
        for i in range(n):
            if i == k : continue
            for j in range(n):
                if j==k or j==i : continue
                D[i][j] = min(D[i][k]+D[k][j],D[i][j])
    return D

def convertG2D(v_list, g) : 
    D=[]
    i = 0
    for s in v_list:
        D.append([])
        j = 0
        for d in v_list:
            if s == d :
                D[i].append(0)
            else :
                w = g.edgeweight((s, d))
                if w is None:
                    D[i].append(float('inf'))
                else:
                    D[i].append(w)
            j = j + 1
        i= i + 1
    return D

def D_print(v_list, D):
    print ("%3s"%"D", end= ' ')
    for v in v_list:
        print ("%3s"%v, end=' ')
    print ()
    for row in D:
        print ("%3s"%v_list[D.index(row)], end= ' ')
        for d in row:
            print ("%3s"%d, end=' ')
        print ()

if __name__=='__main__':
    #Test Data #1
    #Directed Graph :
    start = time.time()
    print()
    print("음수 가중치가 없는 그래프:")         
    V_tuple = ('a', 'b', 'c', 'd')
    EW_dict = {('a','b'):8, ('a','d'):1,
                ('b','c'):1, ('c','a'):4, 
                ('d','b'):2, ('d','c'):9}
    g = Graph_Weighted(V_tuple, EW_dict, undirected=False)
    g.print()
    print()
    print("그래프에서 변환된 최초의 거리산출행렬 D:")
    D = convertG2D(V_tuple, g)
    D_print(V_tuple, D)
    print()
    for i in range(1,1000):
        D = allPairsShortest(D)
    print()
    print("모든쌍최단경로의 거리산출행렬 D:")
    D_print(V_tuple, D)


    #Test Data #2
    #Directed Graph :z
    print()
    print("음수 가중치가 있는 그래프(단, 음수 가중치 싸이클은 없음.):")        
    V_tuple = ('1', '2', '3', '4', '5')
    EW_dict = {('1','2'):4, ('1','3'):2,('1','4'):5,
                ('2','3'):1,('2','5'):4,
                ('3','1'):1, ('3','2'):3,('3','5'):4,
                ('4','1'):-2, ('4','5'):2,
                ('5','2'):-3, ('5','3'):3,('5','4'):1}    
    g = Graph_Weighted(V_tuple, EW_dict, undirected=False)
    g.print()
    print()
    print("그래프에서 변환된 최초의 거리산출행렬 D:")
    D = convertG2D(V_tuple, g)
    D_print(V_tuple, D)
    print()
    D = allPairsShortest(D)
    print()
    print("모든쌍최단경로의 거리산출행렬 D:")
    D_print(V_tuple, D)
    print("\ntime :", time.time() - start)
