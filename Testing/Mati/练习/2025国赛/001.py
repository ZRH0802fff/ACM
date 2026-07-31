import sys;
data=list(map(int,sys.stdin.read().split()))
n,k=data[0],data[1]
arr=data[2:]
ans=set()
for num in arr:
    ans.add(num)
ans=list(ans)
ans.sort()
fn=len(ans)
if k-1<fn:
    print(ans[k-1])
else:
    print(-1)