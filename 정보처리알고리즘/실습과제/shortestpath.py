def shortestPath_Dijkstra(g, s):
    ##입력: 가중치 그래프 G=(V,E), |V|=n , |E|=m
    ##출력: 출발점 s로부터 (n-1)개의 점까지 각각 최단 거리를 저장한 배열 D, 경로를 저장한 배열 P

    ##1. 배열 D를 ∞로 초기화시킨다. 단, D[s]=0으로 초기화한다.
    ##          // 배열 D[v]에는 출발점 s로부터 점 v까지의 거리가 저장된다.
    D = {}     # 최단경로의 값이 저장되는 딕션너리.
    P = {}     # 최단경로의 값이 정해질 때의 선분의 시작점을 기억해두는 딕션너리, 
    D[s] = 0  # 출발점 s를 목적지로 한 최단경로 값은  0 이다.
    P[s] = s  # 출발점 s로 오게 되는 선분의 시작점은 다시 자기자신이라고 가정한다.
    ##2. while (s로부터의 최단거리가 확정되지 않은 점이 있으면) {
    determined = []     # 최단거리가 확정된 점들은 최초 공집합으로 초기화한다.
    undetermined = list(g.vertexes())  # 확정되지 않은 점들을 최초 모든 점들로 초기화한다.
    while( len(undetermined) > 0 ) :
    ##3.    현재까지 s로부터 최단 거리가 확정되지 않은 각 점 v에 대해서
    ##      최소의 D[v]의 값을 가진 점 vmin을 선택하고,
    ##      출발점 s로부터 점 vmin까지의 최단 거리 D[vmin]을 확정시킨다.
        v_min=None
        d_min = float('inf')
        for v in undetermined:         # 확정되지 않은 점들에서 v_min을 찾는다.
            d = D.get(v, float('inf') )  # D[v]의 값이 아직 없으면, 무한대로 설정한다.
            #TODO 
            #TODO 
            #TODO 
        determined.append(v_min)   # 찾아진 v_min을 확정된 점들에 추가한다.
        undetermined.remove(v_min) # 찾아진 v_min을 확정되지 않은 점들에서 제거한다.
    ##4.    s로부터 현재보다 짧은 거리로 점 vmin을 통해 우회 가능한 각 점 w에 대해서
    ##      D[w]를 갱신한다. }
        for e in g.edges_started_from(v_min):    # v_min을 시작점으로 한 모든 선분들에 대해서,  
            if e[1] not in determined :                # 선문의 끝점이 최단거리가 확정이 되지 않았다면,     
                new_d = D[v_min] + g.edgeweight(e)
                if (D.get(e[1])) :          # 그전에 이미 어떤 값을 가지고 있다면, 기존값과 비교해서 갱신한다.  
                    #TODO
                    #TODO  
                    #TODO  
                else :   # 그전에 어떤 값을 가지고 있지 않다면, infinity로 간주하고 새로 값을 할당한다.
                    #TODO 
                    #TODO 
    ##5. return D
    return D, P
if __name__ == "__main__":
    
