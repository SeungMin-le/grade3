from ch05_0_graphutils_v20 import *
import time
def shortestPath(g, s):
    ##입력: 가중치 그래프 G=(V,E), |V|=n , |E|=m
    ##출력: 출발점 s로부터 (n-1)개의 점까지 각각 최단 거리를 저장한 배열 D

    ##1. 배열 D를 ∞로 초기화시킨다. 단, D[s]=0으로 초기화한다.
    ##          // 배열 D[v]에는 출발점 s로부터 점 v까지의 거리가 저장된다.
    D = {}
    D[s] = 0
    ##2. while (s로부터의 최단 거리가 확정되지 않은 점이 있으면) {
    determined = []
    undetermined = list(g.vertexes())
    while( len(undetermined) > 0 ) :
    ##3.    현재까지 s로부터 최단 거리가 확정되지 않은 각 점 v에 대해서
    ##      최소의 D[v]의 값을 가진 점 vmin을 선택하고,
    ##      출발점 s로부터 점 vmin까지의 최단 거리 D[vmin]을 확정시킨다.
        v_min=None
        d_min = float('inf')
        for v in undetermined:
            d = D.get(v, float('inf') ) 
            if d < d_min :
                v_min = v
                d_min = d 
        determined.append(v_min)
        undetermined.remove(v_min)
    ##4.    s로부터 현재보다 짧은 거리로 점 vmin을 통해 우회 가능한 각 점 w에 대해서
    ##      D[w]를 갱신한다. }
        for e in g.edges_started_from(v_min):
            if e[1] not in determined :
                if (D.get(e[1])) : 
                    D[e[1]] = min(D[v_min] + g.edgeweight(e), D[e[1]])
                else :   # infinity
                    D[e[1]] = D[v_min] + g.edgeweight(e)
    ##5. return D
    return D

if __name__ == "__main__" :
    start = time.time()
    #Undirected Graph         
    V_tuple = ('서울', '천안', '원주', '논산', '대전', '강릉', '광주', '대구', '포항', '부산')
    EW_dict = {('서울','천안'):12, ('서울','원주'):15,
                ('천안','논산'):4, ('천안','대전'):10,
                ('논산','대전'):3,
                ('대전','대구'):10, ('부산','대구'):9, 
                ('원주','강릉'):21,('원주','대구'):7,('강릉','포항'):25,
                ('포항','대구'):19,('포항','부산'):5,
                ('논산','광주'):13,('광주','부산'):15, }
    g = Graph_Weighted(V_tuple, EW_dict, undirected=True)
    s = '서울'
    for i in range(1,1000):

        d = shortestPath(g, s)
    print ("출발지:", s)
    for v in V_tuple :
        print ( v, ":", d[v], end=', ' )
        
    print("\ntime :", time.time() - start)
    
