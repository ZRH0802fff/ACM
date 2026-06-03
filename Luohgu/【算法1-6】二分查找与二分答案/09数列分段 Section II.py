import sys 
data=list(map(int,sys.stdin.read().split()))
n,m=data[0],data[1]
arr=data[2:]

def ok (msum):
    op=0
    tsum=0
    idx=0
    while idx<n and op<m:
        if idx+1==n:
            tsum+=arr[idx]
            if tsum<=msum: op+=1
            else:op+=2
            return op<=m
        tsum+=arr[idx]
        if tsum>msum:
            op+=1
            tsum=arr[idx]
        idx+=1
    return False

l,r=max(arr),sum(arr)
ans=r
while l<=r:
    mid=(l+r)//2
    if ok(mid):
        r=mid-1
        ans= mid if mid <ans else ans
    else:
        l=mid+1
print(ans)  