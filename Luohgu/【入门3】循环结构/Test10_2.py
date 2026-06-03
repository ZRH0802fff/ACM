import math

l=int(input())

def isPrimes(num):
    if num<=1:
        return False
    for i in range (2,int(math.sqrt(num))+1):
        if num%i==0:
            return False
    return True

total=0
count=0
n=1
primes=[]
while l>total:
    if isPrimes(n):
        total+=n
        count+=1
        primes.append(n)
    n+=1

for i in range(len(primes)-1):
    print(primes[i])
if l==total:
    print(primes[count-1])
    print(count)
else:
    print(count-1)