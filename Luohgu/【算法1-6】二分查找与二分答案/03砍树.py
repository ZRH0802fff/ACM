import sys
data=list(map(int,sys.stdin.read().split()))
n,m=data[0],data[1]
book=data[2::]
max_num=0
for num in book:
    if num>max_num: max_num=num

def ok(kan):
    ans=0
    for num in book:
        if num>kan:
            ans+=num-kan
    return ans>=m

l,r=0,max_num
ans=0
while l<=r:
    mid=(l+r)//2
    if ok(mid):
        l=mid+1
        ans=mid if mid >ans else ans
    else:
        r=mid-1
print(ans)
