from ch04_graphutils_v10 import *
from ch04_kruskalmst_v00 import *
from ch04_primmst_v00 import  *

import time

def time_experiment(n, m) :
    g_gen = generateRandomGraph(n, m)
##    g_gen.print()
    print("Node #:", len(g_gen.vertexes()),
          " Vertexes #: ", len(g_gen.edges()) )
    
    t1 = time.process_time()
    tk = kruskal_MST(g_gen)
    elapsed_time1 = time.process_time() - t1
    
    print("Kruskal Algorithm:")
##    tk.print()
    print("total weights:", tk.total_weights())
    print ("Execution Time : %.4f sec"%elapsed_time1)
    print ("--------------------------------------------")

##    g_gen.print()
    print("Node #:", len(g_gen.vertexes()),
          " Vertexes #: ", len(g_gen.edges()) )

    t2 = time.process_time()
    tp = prim_MST(g_gen)
    elapsed_time2 = time.process_time() - t2

    print("Prim Algorithm:")
##    tp.print()
    print("total weights:", tp.total_weights())
    print ("Execution Time : %.4f sec"%elapsed_time2)
    print ("--------------------------------------------")


if __name__ == "__main__" :

    # 주의사항: 실행시간 측정시에는 중간에 출력되는 중간 결과를 출력하지 않도록
    # 프로그램의 코드를 수정하고서 호출이 되도록 한다.
    # 화면출력하는 작업은 상당한 시간지연을 유발하게 됨.

    for (n, m) in [(10, 50), (100, 500), (200, 500), (300, 500), (400, 600), (500, 1000) ] :
        # (노드수, 링크수)
        time_experiment(n, m)
