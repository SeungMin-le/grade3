def CoinChange2(pMoney,coins):
    change = pMoney
    k=sorted(coins,reverse=True)
    
    numCoins={}
    for i in k:
        numCoins[i] =0
    for i in k:
        while change>=i:
            change-=i
            numCoins[i]+=1
   
    
    return numCoins

if __name__ == "__main__" :
    coins=(1,10,50,100,160,500)
    numCoins=CoinChange2(485,coins)
    
    print(numCoins)
