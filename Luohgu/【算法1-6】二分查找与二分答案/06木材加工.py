import sys
data=list(map(int,sys.stdin.read().split()))
n,k=data[0],data[1]
arr=data[2:]
#print(arr,sum(arr))
r=sum(arr)//k
if r<=1:
    print(r)
    exit()
l=1

def ok(tl):
    ans=0
    for num in arr:
        ans+=num//tl
    return ans>=k

ans=0
while l<=r:
    mid=(l+r)//2
    if ok(mid):
        l=mid+1
        ans=mid if mid>ans else ans
    else:
        r=mid-1
print(ans)        