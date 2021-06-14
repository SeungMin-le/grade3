
def fractionalKnapsack(V, c):
##입력: n개의 물건, V 각 물건의 무게와 가치, 배낭의 용량 C
##출력: 배낭에 담은 물건 리스트 L과 배낭에 담은 물건의 가치 합 v
    # n: 불필요한 입력, V: 딕셔너리형 {'물건명':(무게, 가치), .....}, V['물건묭'] = (무게, 가치),
    # c " 숫자형(int 또는 float)
    # L : list형, [('물건명', 실은무게), ....], v : 가치의 합(int)
   

    S = []
    for item in V.keys():
        S.append((item,V[item][1]/V[item][0]))

    S.sort(reverse = True,key = lambda a: a[1])
    print("Sorted:",S)

    L = []
    v = 0
    w = 0


    if(len(S)>0):
        x= S.pop(0)
    else:
        return L,v
    

    while w+V[x[0]][0] <= c :

        L.append((x[0],V[x[0]][0]))

        w=w+V[x[0]][0]

        v= v+V[x[0]][1]

        if len(S)>0:
            x=S.pop(0)
        else :
            break
    if c-w>0:
        

      
        L.append((x[0],(c-w)))

    
        v = v+(c-w)*x[1]

    
    return L, v

if __name__=="__main__" :
    
    mList = { '주석':(50, 5), '백금':(10,60), '은':(25, 10), '금':(15, 75) }
    sackWt = 40
    print (mList, sackWt)
    
    sack_mList, sack_Value = fractionalKnapsack(mList, sackWt)
    print (sack_mList, sack_Value)
    
