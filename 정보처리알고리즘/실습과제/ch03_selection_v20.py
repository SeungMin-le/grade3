from random import randint
import timeit
def pivotSplit ( A, left, p, right ) :
    # print("....bef....", left, p, right, A )
    A[p], A[left] = A[left], A[p]  # A[left]와 A[p]의 자리를 바꾼 후,
    i = left+1                              # 피봇 A[left]와 배열 A[left+1]~A[right]의 각 원소A[i]를 
    j = right                                # 비교하여 피봇보다 작은 숫자는 A[left]~A[p-1]로 옮기고, 
    while ( i <= j ) :                       # 피봇보다 큰 숫자들은 A[p+1]~A[right]롤 옮기며, 
        # print("............", i, j, A )       
        while ( i <= j and A[i] <= A[left] ) :  # it is OK
            i = i + 1
        while ( i <= j and A[j] >= A[left] ) : # it is OK
            j = j - 1
        if ( i < j ) :
            A[i], A[j] = A[j], A[i]
            i = i + 1
            j= j - 1
    new_p = i-1
    A[left], A[new_p] = A[new_p], A[left]      #  피봇 A[left]는 A[p]에 놓는다.
    # print("....aft....", left, new_p, right, A )
    return new_p


def selection(A, left, right, k):
    ##    Selection(A, left, right, k)
    ##    입력: A[left]~A[right]와 k, 단, 1≤k≤|A|, |A|=right-left+1
    ##    출력: A[left]~A[right]에서 k 번째 작은 원소
    ##    1.  피봇을 A[left]~A[right]에서 랜덤하게 선택하고,

    p = randint(left, right)
    p = pivotSplit(A, left, p, right )
   
    S=p-left
   
    ##    3. if ( k ≤ S ) Selection(A, left, p-1, k) // Small group에서 찾기
    if k<=S:
        return selection(A,left,p-1,k)
    
    elif k== S + 1 :
        return A[p]
    else:
        return selection(A,p+1,right,k-S-1)
  
def test_fn(n):
        A = sample(range(10000), n)    # sample()함수에 의해 n개의 무작위 수를 자동 추출
        Origin_A = tuple(A)
        print ()
        ##print ('Original Data : ', Origin_A )
        start_time1 = timeit.default_timer()
        sA = sorted(Origin_A)
        end_time1 = timeit.default_timer()
        ##print ('Sorted  Data : ', sorted(Origin_A))
        
        ex_time1=end_time1-start_time1
        
        
        k = randint(1, n)  # random of (1, 2, ..., n)
        print ("expected value in rank ", k, " : ", sA[k-1] )
        start_time2 = timeit.default_timer()
        result = selection (A, 0, len(A)-1, k)
        end_time2 = timeit.default_timer()
        ex_time2=end_time2-start_time2
        print ("selection value in rank ", k, " : ", result )
        print("excute time: %f" %ex_time1)
        print("excute time: %f" %ex_time2)
if __name__=='__main__' :
    from random import sample
    ##test_fn(10)
    num = 1000
    i=1
    while i<num:
        test_fn(100)
        i+=1
    
