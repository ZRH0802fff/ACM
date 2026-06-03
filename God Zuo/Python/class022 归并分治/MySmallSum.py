import sys
MAXN=100001
arr=[0]*MAXN
temp=[0]*MAXN

def smallSum(l,r):
    if l==r :
        return 0
    m=(l+r)//2
    return smallSum(l,m)+smallSum(m+1,r)+merge(l,m,r)

def merge(l,m,r):
    ans=0
    i=l
    sum_val=0
    for j in range(m+1,r+1):
        while i<=m and arr[i]<=arr[j]:
            sum_val+=arr[i]
            i+=1
        ans+=sum_val
    
    i=l
    a=l
    b=m+1
    while a<=m and b<=r:
        if arr[a]<=arr[b]:
            temp[i]=arr[a]
            a+=1
        else:
            temp[i]=arr[b]
            b+=1
        i+=1
    while a<=m:
        temp[i]=arr[a]
        a+=1
        i+=1
    while b<=r:
        temp[i]=arr[b]
        b+=1
        i+=1
    
    for k in range(l,r+1):
        arr[k]=temp[k]
    
    return ans

data=sys.stdin.read().split()
idx=0
while idx<=len(data):
    n=int(data[idx])
    idx+=1
    for i in range(n):
        arr[i]=int(data[idx])
        idx+=1
    print(smallSum(0, n - 1))