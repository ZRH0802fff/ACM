import sys
from collections import Counter
data=list(sys.stdin.read().split())
n,m=int(data[0]),int(data[1])
arr=['']*(n)
idx=2
for i in range(n):
    arr[i]=data[idx]
    idx+=1
ans=0
for j in range(m):
    t=[]
    for i in range(n):
        t.append(arr[i][j])
    tc=Counter(t)
    #print(t,tc,ans)
    tans=0
    for ch in tc:
        tans+=tc[ch]*(n-tc[ch])
    ans+=tans//2
print(ans)

