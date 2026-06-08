import sys
data=list(map(int, sys.stdin.read().split()))
n,m=data[0],data[1]
mi,ma=float('inf'),float('-inf')
for i in range(2,2+m):
    t=data[i]
    if t<mi: mi=t
    if t>ma: ma=t
ans=[0]*(n+1)
for i in range(1,n+1):
    t1=abs(i-mi)
    t2=abs(i-ma)
    ans[i]=t1 if t1>t2 else t2
print(' '.join(str(ans[i]) for i in range(1,n+1)))
