import math
n=int(input())
book=map(int,input().split())

def isPrime(num):
    if num<=1:
        return False
    if num==2:
        return True
    if num%2==0:
        return False
    for i in range(3,int(math.sqrt(num))+1,2):
        if num%i==0:
            return False
    return True

f=''
for i in book:
    if isPrime(i):
        f+=str(i)+' '
print(f[:-1])