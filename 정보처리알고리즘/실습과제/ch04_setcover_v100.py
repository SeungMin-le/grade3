#  잘못된 코드 부분을 수정함. 

def commonList(A, B):
    A = set(A)
    B = set(B)
    C = A.intersection(B)
    return list(C)

def setCover(U, F):
##입력: U:커버할 항목들의 전체 집합, F={Si}, i=1,⋯,n, Si:부분커버집합
##출력: 집합 커버 C   : 부분커버집합들의 집합
##

    C=[]
    U = list(U)
    F = list(F)
    F.sort(reverse=True, key=lambda S: len(commonList(S[1],U)) )
              

    while len(U)>0 :
        S = F.pop(0)
        for i in S[1] :
            n = U.count(i)
            for j in range(n):
                U.remove(i)
        C.append(S)
        F.sort(reverse=True, key=lambda S: len(commonList(S[1],U)) )

    return C

if __name__=='__main__':
    U = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    S1 = ('S1', (1,2,3,8))
    S2 = ('S2', (1,2,3,4,8))
    S3 = ('S3', (1,2,3,4))
    S4 = ('S4', (2,3,4,5,7,8))
    S5 = ('S5', (4,5,6,7))
    S6 = ('S6', (5,6,7,9,10))
    S7 = ('S7', (4,5,6,7))
    S8 = ('S8', (1,2,4,8))
    S9 = ('S9', (6,9))
    S10=('S10', (6,10))
##    F = {S7, S8, S9, S10, S1, S2, S3, S4, S5, S6}
    F = {S10, S9, S8, S7, S6, S5, S4, S3, S2, S1}
    C = setCover(U,F)
    print (C)
    print ()

    U = ('a', 'b', 'c','d','e','f','g','h','i','j','k','l','m','n','o')
    S1 = ('S1', ('a','b','c','d','e','m'))
    S2 = ('S2', ('g','c','i'))
    S3 = ('S3', ('a','f'))
    S4 = ('S4', ('d','o','l'))
    S5 = ('S5', ('b','j','l','n','k','g'))
    S6 = ('S6', ('e','h','o','n','i'))
    S7 = ('S7', ('k','m'))
    S8 = ('S8', ('j','m'))
    F = (S1, S2, S3, S4, S5, S6, S7, S8)
    
    C = setCover(U,F)
    print (C)
    
