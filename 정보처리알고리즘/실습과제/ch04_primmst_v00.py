from ch03_quicksort_v30 import quickSort
from ch04_graphutils_v10 import * 
from random import randint

def prim_MST(g):
    # 입력: 가중치 그래프 G=(V, E), n개의 점과 m개의 선분
    # 출력: 최소 신장 트리
    n = len(g.vertexes())
    m = len(g.edges())

    #1. 그래프 G에서 임의의 점 p를 시작점으로 선택하고, D[p]=0으로 놓는다.

    #    // 배열 D[v]는 점 v에 대하여,
    #    // T에 속한 점과 연결되어 있는 선분의 최소 가중치를 저장해두는 배열이다.
    D = {}   # 파이선 구현에서는 배열 구조 대신 딕션너리 구조로 D를 표현한다. 
    v_list_remained = list(g.vertexes())
   
    #p = v_list_remained.pop( randint(0, len(v_list_remained)-1) )
    p = v_list_remained.pop(0)
    
    D[p] = 0

    #2. for (점 p가 아닌 각 점 v에 대하여) {       // 배열 D의 초기화 과정(2~6)
    for v in v_list_remained:
    
    #3.     if ( 선분 (p,v)가 그래프에 있으면 )
         w_pv = g.edgeweight ( (p, v) )
         print(w_pv)
         if w_pv : 

    #4.         D[v] = 선분 (p,v)의 가중치
             D[v] = w_pv 

    #5.     else 
    #6.         D[v]=∞
         else:
             D[v] = float('inf')    
    #   } // end of for 

    #T= {p}     // 초기에 트리 T는 점 p만을 가진다.
    t =  Tree_Weighted([p], dict({}))

    #8. while (T에 있는 점의 수 < n) {
    updated = True
    while (updated and len(t.vertexes()) < n ) : 

    #9.     T에 속하지 않은 각 점 v에 대하여,
    #                D[v]가 최소인 점 vmin과 연결된 선분 (u,vmin)을 T에 추가한다.
    #                단, u는 T에 속한 점이고, 점 vmin은 T에 새로 추가된다.
        d_min=float('inf')        
        updated = False
        for v in t.vertexes():
            for e in g.edges_started_from(v):
                 if e[1] in v_list_remained :
                    if g.edgeweight(e) < d_min :
                        d_min = g.edgeweight(e)
                        u = v
                        v_min = e[1]
                        updated = True
        if ( updated ) :   
            t.addedge( (u, v_min), d_min )
            v_list_remained.remove( v_min )
            
    #10.   for (T에 속하지 않은 각 점 w에 대해서) {  // D[w]를 갱신 과정
    #11.         if (선분 (vmin,w)의 가중치 < D[w])      // 새로 추가된 점 vmin과 비교하여
    #                   D[w] = 선분 (vmin,w)의 가중치  // 기존 값보다 작으면 갱신한다.
            for e in g.edges_started_from(v_min):
               if e[1] in v_list_remained:
                    D[e[1]] = g.edgeweight( e )
    #               }
    #           }
    return t


if __name__ == "__main__" :

    V_tuple = ('a', 'b', 'c', 'd', 'e', 'f')
    EW_dict = {('a','b'):3, ('a','d'):2, ('a','e'):4,
           ('b','c'):1, ('b','d'):4, ('b','f'):2,
           ('c','f'):1,
           ('d','e'):5, ('d','f'):7,
           ('e','f'):9}
    
##    V_tuple = ('a', 'b', 'c', 'd', 'e', 'f')
##    EW_dict = {('a','b'):8, ('a','d'):2, ('a','e'):4,
##           ('b','c'):1, ('b','d'):4, ('b','f'):2,
##           ('c','f'):1,
##           ('d','e'):3, ('d','f'):7,
##           ('e','f'):9}

    g = Graph_Weighted(V_tuple, EW_dict, undirected=True)
    g.print()
    
    p_tree = prim_MST(g)
    p_tree.print()
