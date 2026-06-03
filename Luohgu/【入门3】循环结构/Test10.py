import math

l=int(input())

def isPrimes(num):
    if num<=1:
        return False
    for i in range (2,int(math.sqrt(num))+1):
        if num%i==0:
            return False
    return True
sumPrimes=[0]
index=1
for i in range(1,1000):
    if isPrimes(i):
        sumPrimes.append(sumPrimes[index-1]+i)
        index+=1
for i in range(len(sumPrimes)):
    if sumPrimes[i]>l:
        print(i-1)