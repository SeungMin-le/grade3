# ver3.0
# 비교에 사용할 키 값을 리턴하는 람다함수를 간단하게 정의해서 줌으로써,
# 다양한 데이타 객체의 리스트에 대해서도 퀵정렬할 수 있게 함. 

def quickSort(S, left=0, right=-2, descend=False, key=lambda a: a):

    def pivotSplit(S, left, p, right, descend=False, key=lambda a : a ):
        S[p], S[left] = S[left], S[p]
        i = left + 1
        j = right
        while ( i <= j ) :
            while ( i <= j and ( ( descend==False and key(S[left]) >= key(S[i]) ) or
                                 (descend == True and key(S[i])>= key(S[left]) ) )):
                i = i + 1
            while ( i <= j and ( ( descend==False and key(S[j]) >= key(S[left]) ) or
                                 (descend == True and key(S[left])>= key(S[j]) ) ) ) :
                j = j - 1
            if ( i < j ) :
                S[i], S[j] = S[j], S[i]
                i = i + 1
                j = j - 1
        new_p = i - 1
        S[left], S[new_p] = S[new_p], S[left]
        return new_p

    if right == -2 : right = len(S)-1   # right 인자가 생략되면, 맨끝의 항목의 인덱스로 처리. 
    if (left < right ) :
        p = int( (left + right) / 2 )
        p = pivotSplit(S, left, p, right, descend, key)
        quickSort(S, left, p-1, descend, key )
        quickSort(S, p+1, right, descend, key)

def test_fn(A):
    Origin_A = tuple(A)
    print ('Original Data : ', Origin_A )
    print ('Sorted  Data : ', sorted(Origin_A, reverse=False))
    quickSort(A, 0, len(A)-1, descend=False, key=lambda x: x)
    print ('QuickSorted : ', A )
    print ('Sorted  Data : ', sorted(Origin_A, reverse=True))
    quickSort(A, 0, len(A)-1, descend=True)
    print ('QuickSorted : ', A )
    print ()



if __name__=='__main__' :
    from random import sample
    
    for i in range(1, 4):
        print ("Random Test : ", i)
        A = sample(range(100), 10)    # sample()함수에 의해 10개의 무작위 수를 자동 추출
        test_fn(A)

    players = [ ('양수진', (72, 68, 68, 69)),
                    ('박지은', (68, 72, 73, 69)),
                    ('안신애', (70, 71, 70, 70)),
                    ('최나연', (69, 68, 72, 69)),
                    ('이수지', (70, 69, 70, 70)),
                    ('신현주', (69, 70, 71, 70)),
                    ('유소연', (70, 69, 68, 67)),
                    ('박세리', (70, 71, 69, 70)),
                    ('서희경', (71, 70, 68, 67)),
                    ('박인비', (68, 67, 68, 69))]
              
    class Player:
        def __init__(self, name, score):
            self.name=name
            self.score=score
            self.parscore=[s-72 for s in self.score]
            self.totalps=0
            for ps in self.parscore:
                self.totalps = self.totalps + ps
                
    pRec_origin = []
    for name, score in players:
        new = Player(name, score)
        pRec_origin.append(new)
        print(name, score, new.totalps)

    print("My Quick Sort:")
    pRec1 = pRec_origin[:]
    quickSort(pRec1, descend=False, key=lambda p: p.totalps)
    for p in pRec1: 
        print (p.name, p.totalps)

    print("List Module Sort:")
    pRec2 = pRec_origin[:]
    pRec2.sort(key=lambda x: x.totalps)
    for p in pRec2: 
        print (p.name, p.totalps)

        
    
