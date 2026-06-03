import math
import sys
sys.setrecursionlimit(2000000)
n,k=map(int ,input().split())
arr=list(map(int ,input().split()))

def isPrime(num):
    if num<=1:
        return False
    if num==2:
        return True
    if num %2==0:
        return False
    for i in range(3,int(math.sqrt(num))+1,2):
        if num%i==0:
            return False
    return True

ans=0

def dfs(con,i,sum):
    #print(con,i,sum)
    global ans
    if con==k:
        if isPrime(sum):
            ans+=1
        return
    if i==n:
        return
    if con+(n-i)<k:
        return
    dfs(con+1,i+1,sum+arr[i])
    dfs(con,i+1,sum)

dfs(0,0,0)
print(ans)
