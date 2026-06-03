import sys
data=list(map(int,sys.stdin.read().split()))
L,n,k=data[0],data[1],data[2]
arr=[0]*(n-1)
idx=4
for i in range(n-1):
    arr[i]=data[idx]-data[idx-1]
    idx+=1

def ok(num):
    ans=0
    for cur in arr:
        #print(cur,num)
        if cur%num==0:
            ans-=1
        ans+=cur//num
    return ans<=k

l,r,ans=1,L,L
while l<=r:
    mid=(l+r)//2
    if ok(mid):
        ans=mid if mid <ans else ans
        r=mid-1
    else:
        l=mid+1
print(ans)