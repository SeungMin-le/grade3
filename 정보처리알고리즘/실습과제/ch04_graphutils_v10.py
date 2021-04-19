class Graph_Weighted:
    def __init__(self, vertexes, edgeweights, undirected=True):
        self.__v_set__ = set(vertexes)
        self.__ew_dict__ = dict(edgeweights)
        if undirected and self.check_undirected() :
            self.__undirected__=True
        else :
            self.__undirected__=False

    def undirected(self):
        return self.__undirected__ 

    def check_undirected(self):
        vertexes= self.__v_set__
        edgeweights = self.__ew_dict__

        for v in vertexes :
            edges = list(edgeweights.keys())
            for e in edges:
                if e[0] == v : # if there is found a edge starting from v
                    reverse_e = (e[1], e[0])
                    #edgeweights.setdefault( reverse_e, edgeweights[e])
                    if edgeweights.get(reverse_e) : return None
        return True

    def vertexes(self):
        return self.__v_set__

    def edges(self):
        return self.__ew_dict__.keys()

    def edges_started_from(self, v):
        edges = [e for e in self.edges() if e[0] == v]
        if self.__undirected__ :
            for e in self.edges() :
                if e[1] == v : edges.append( (e[1], e[0]) )
        return edges         

    def edgeweights(self):
        return self.__ew_dict__
    
    def edgeweight(self, e):
        if self.__undirected__ :
            reverse_e = (e[1], e[0])
            return  self.__ew_dict__.get(e) or self.__ew_dict__.get(reverse_e)
        return self.__ew_dict__.get(e)

    def total_weights(self):
        weight_sum = 0
        for e in self.edges() :
            weight_sum = weight_sum + self.edgeweight(e)
        return weight_sum        

    def addedge(self, e, w):
        if self.__undirected__ :
            reverse_e = (e[1], e[0])
            if self.__ew_dict__.get(e) :
                self.__ew_dict__[e] = w
                return
            elif self.__ew_dict__.get(reverse_e) :
                self.__ew_dict__[reverse_e] = w
                return
        self.__v_set__.add(e[0])
        self.__v_set__.add(e[1])
        self.__ew_dict__[e]=w
        
    def deledge(self, e):
        self.__ew_dict__.pop(e)

    def print(self):
        if self.__undirected__ : print ("Undirected Weighted Graph:")
        else : print ("Directed Weighted Graph:" )
        print ("Node # : ", len(self.__v_set__), "Edges # : ", len(self.__ew_dict__) )
        for v in self.vertexes() :
            print("vertex:",v, end="->")
            for e in self.edges() :
                if e[0] == v : print (e, ":", self.edgeweight(e), end=', ')
            print()

class Tree_Weighted(Graph_Weighted):
    def __init__(self, vertexes, edgeweights):
        Graph_Weighted.__init__(self, vertexes, edgeweights, undirected=True)

    def check_cycle_with_edge(self, e):
        # 트리에서의 사이클 체크. 
        # 구현 난이도 : 상
        def expand_childs_not_in_visited(node, visited):
            childs = []
            for e in self.edges_started_from(node):
                if e[1] not in visited : childs.append(e[1]) 
            return childs            
        start_node = e[0]
        end_node = e[1]
        n = len(self.vertexes())
        frontier = []
        visited = set([])  # empty set
        frontier.append( e[0] ) # list of FIFO queue --> frontier.pop(0)
        while ( len(visited) < n and len(frontier) > 0 ) :
            node = frontier.pop(0)
            if  node == end_node : return True  # Cycle to be made !!!
            visited.add(node)
            childs = expand_childs_not_in_visited(node, visited)
            frontier = frontier + childs
        return False

    def check_cycle_with_edge2(self, e):
        # 트리에서의 사이클 체크.(연습문제 #5의 아이디어 반영하기) 
        # 구현 난이도 : 최상
        # 자료구조에서 배운 disjoint set의 union() and find() 연산으로 구현하기
        # TODO # TODO  # TODO # TODO   # TODO # TODO
        # TODO # TODO  # TODO # TODO   # TODO # TODO
        return False

    def print(self):
        print ("Weighted Tree:")
        weight_sum = 0
        for v in self.vertexes() :
            print("vertex:",v, end="->")
            for e in self.edges() :
                if e[0] == v :
                    print (e, ":", self.edgeweight(e), end=', ')
                    weight_sum = weight_sum + self.edgeweight(e)
            print()
        print("Total Weights : ", weight_sum)

    def addedgeWithCycleCheck(self, e, w):
        if self.check_cycle_with_edge(e) :
            return None
        self.__v_set__.add(e[0])
        self.__v_set__.add(e[1])
        self.__ew_dict__[e]=w
        return True

def generateRandomGraph(n, m):
    # n: 노드 수  m: 에지 수 
    from random import sample, randint
    g = Graph_Weighted([], dict({}) )
    v_list = range(n)
    # Make Ring Topology
    for v in v_list[:-1]:
        e = (v, v+1)
        w = randint(1,100)
        g.addedge(e, w)
    e = (n-1, 0)
    w = randint(1,100)
    g.addedge(e, w)
    for i in range(m):
        e = tuple(sample(v_list, 2))
        w=randint(1, 100)
        g.addedge(e, w)
    return g

if __name__ == "__main__" :
    
    #Undirected Graph         
    V_tuple1 = ('a', 'b', 'c', 'd', 'e', 'f')
    EW_dict1 = {('a','b'):3, ('a','d'):2, ('a','e'):4,
           ('b','c'):1, ('b','d'):4, ('b','f'):2,
           ('c','f'):1,
           ('d','e'):5, ('d','f'):7,
           ('e','f'):9}
    g1 = Graph_Weighted(V_tuple1, EW_dict1, undirected=True)
    g1.print()
    print("Total Weights : ", g1.total_weights())
    
    V_tuple2 = ('a', 'b', 'c', 'd', 'e', 'f')
    EW_dict2 = {('a','b'):8, ('a','d'):2, ('a','e'):4,
           ('b','c'):1, ('b','d'):4, ('b','f'):2,
           ('c','f'):1,
           ('d','e'):3, ('d','f'):7,
           ('e','f'):9}
    g2 = Graph_Weighted(V_tuple2, EW_dict2, undirected=False)
    g2.print()
    print("Total Weights : ", g2.total_weights())

    #Tree Generation 
    V_tuple3 = ('a', 'b', 'c', 'd', 'e', 'f')
    EW_dict3 = {('a','b'):8, ('a','d'):2, ('a','e'):4,
           ('b','c'):1, ('b','d'):4, ('b','f'):2,
           ('c','f'):1,
           ('d','e'):3, ('d','f'):7,
           ('e','f'):9, ('c','b'):5 }
    
    t1 = Tree_Weighted([], dict({}))
    for e, w in EW_dict3.items() :
        if not t1.check_cycle_with_edge(e) :
            t1.addedge(e, w)
            print ("Successfuly added: ", e)
        else:
            print ("Cycle caused with : ", e)
    t1.print()
    print("Total Weights : ", t1.total_weights())

    g_gen = generateRandomGraph(10, 50)
    g_gen.print()
    print("Total Weights : ", g_gen.total_weights())
    
    

