from ch03_quicksort_v30 import quickSort
from ch04_graphutils_v10 import *

def kruskal_MST(g):
   
    n = len(g.vertexes())
    m = len(g.edges())
    #1.가중치의 오름차순으로 선분들을 정렬한다. 정렬된 선분리스트를 L이라고 하자.
    L = list(g.edges())
    quickSort(L, descend=False, key=lambda e: g.edgeweight(e))

    
    # 2. T=empty_graph  //트리를 초기화시킨다.
    t =  Tree_Weighted([], dict({}))    
    
    # 3. while(T의 선분수 < n-1 {
    while len(t.edges()) < n-1 and len(L) > 0 :
        #4. L에서 가장 작은 가중치를 가진 선분 e를 가져오고, e를 L에서 제거한다.
        e = L.pop(0)
#
        ##5. if (선분 e가 T에 추가되어 사이클을 만들지 않으면)
        ##6.     e를 T에 추가시킨다.
        if not t.check_cycle_with_edge(e) :
            t.addedge (e, g.edgeweight(e))
   
        ##7. else  // e가 T에 추가되어 사이클이 만들어지는 경우
        ##8.          e를 버린다.
       
        else :
            
            pass

    ##9. return 트리 T    // T는 최소 신장 트리이다.
    return t


if __name__ == "__main__" :

##    V_tuple = ('a', 'b', 'c', 'd', 'e', 'f')
##    EW_dict = {('a','b'):8, ('a','d'):2, ('a','e'):4,
##           ('b','c'):1, ('b','d'):4, ('b','f'):2,
##           ('c','f'):1,
##           ('d','e'):3, ('d','f'):7,
##           ('e','f'):9}
    V_tuple = ('a', 'b', 'c', 'd', 'e', 'f', 'g')
    EW_dict = {('a','b'):18, ('a','c'):8, ('a','d'):2, ('a','f'):10,
           ('b','d'):12, ('b','e'):4, ('c', 'f'):5, 
           ('d','e'):14, ('d','f'):3,('d','g'):30, 
           ('e','g'):26, ('f','g'):16}

    g = Graph_Weighted(V_tuple, EW_dict, undirected=True)
    g.print()

    k_tree = kruskal_MST(g)
    k_tree.print()
    
