def mergeList( A, p, k, q ) :
    ##5.    A[p]~A[k]와A[k+1]~A[q]를합병한다.
    # print ("...........", p, k, q, " : ", A)
    B = A[p:k+1]
    C = A[k+1:q+1]
    i =  j = 0
    t = p
    # print ("......before..........", B, " , ", C)
    while ( i < len(B) and j < len(C) ) :
        if ( B[i] > C[j] ) :
            A[t] = B[i]
            t=t+1
            i=i+1
        else :
            A[t] = C[j]
            t=t+1
            j=j+1
    while ( i < len(B) ) :
            A[t] = B[i]
            t=t+1
            i=i+1
    while ( j < len(C) ) :
            A[t] = C[j]
            t=t+1
            j=j+1
    # print (".........merged.......", A[p:q+1])
            

def mergeSort (A, p, q) :
    """ 합병정렬 알고리즘 """
    ##MergeSort(A, p, q)
    ##입력:A[p]~A[q]
    ##출력: 정렬된A[p]~A[q]
    ##1. if ( p < q ) {// 배열의원소의수가2개이상이면
    ##2.    k = ⌊(p+q)/2⌋// k는반으로나누기위한중간원소의인덱스
    ##3.    MergeSort(A,p,k) // 앞부분배열을가지고재귀호출
    ##4.    MergeSort(A,k+1,q)// 뒷부분배열을가지고재귀호출
    ##5.    A[p]~A[k]와A[k+1]~A[q]를합병한다.
    ##      }
    if ( p < q ) :
        k =  int((p + q) / 2)
        mergeSort ( A, p, k )
        mergeSort ( A, k+1, q )
        mergeList ( A, p, k, q )
        print( ".....", p, q, " : ", A)

def compare_list ( a, b ) :
    if len(a) != len(b) : return False
    for k in range(len(a)) :
        if a[k] != b[k] : return False
    return True


def test_fn(A):
    Origin_A = tuple(A)
    print ('Original Data : ', Origin_A )
    print ('Sorted  Data : ', sorted(Origin_A, reverse=True) )
    mergeSort(A, 0, len(A)-1)
    print ('MergeSorted : ', A )
    if compare_list(A, sorted(Origin_A, reverse=True)) : print ("The Same!!!")
    else : print ("Different!!!")
    print ()



if __name__=='__main__' :
##    from random import sample
##    for i in range(1, 11) :
##        print ("Random Test: ", i)
##        A = sample(range(100), 10)    # sample()함수에 의해 10개의 무작위 수를 자동 추출
    A = [17, 51, 58, 62]
    print ('Original Data : ', A )
    mergeSort(A, 0, len(A)-1)
    print ('MergeSorted : ', A )
