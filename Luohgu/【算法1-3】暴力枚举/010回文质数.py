import math
n,m=map(int ,input().split())

def isPrime(num):
    if num<=1: return False
    if num==2: return True
    if num%2==0: return False
    for i in range(3,int(math.sqrt(num))+1,2):
        if num%i==0 : return False
    return True

out=[]
for num in range(n,m+1):
    if num%2==0:continue
    s=str(num)
    if s==s[::-1]:
        if isPrime(num):
            out.append(num)

print('\n'.join(str(x) for x in out))