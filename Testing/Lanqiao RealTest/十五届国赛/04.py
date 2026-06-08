import sys
import heapq
data=list(map(int,sys.stdin.read().split()))
n,m=data[0],data[1]
hq=[0]*n
for i in range(2,n+2):
    hq[i-2]=-data[i]
heapq.heapify(hq)
for i in range(m):
    tmp=-heapq.heappop(hq)
    s1=tmp//2
    s2=tmp-s1
    heapq.heappush(hq,-s1)
    heapq.heappush(hq,-s2)
print(-heapq.heappop(hq))