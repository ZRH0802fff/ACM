import sys
data=list(map(int,sys.stdin.read().split()))
n,p=data[0],data[1]
idx=2
arr=[]
sumsp=0
for _ in range(n):
    arr.append((data[idx],data[idx+1]))
    sumsp+=data[idx]
    idx+=2
if sumsp<=p:
    print(-1)
    exit()

def ok(t):
    re=0.0
    for i in range(n):
        diff=arr[i][0]*t-arr[i][1]
        if diff>0:
            re+=diff
    return re<=p*t

l,r=0.0,1e12
for _ in range(100):
    mid=(l+r)/2.0
    if ok(mid):
        l=mid
    else:
        r=mid
print(f'{l:.10f}')
