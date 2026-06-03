import sys
import heapq

data=list(map(int , sys.stdin.read().split()))
n,m=data[0],data[1]
graph=[[]for _ in range (n+1)]
idx=2
for _ in range(m):
    u,v,w=data[idx],data[idx+1],data[idx+2]
    graph[u].append((w,v))
    graph[v].append((w,u))
    idx+=3
vt=[False]*(n+1)
vt[1]=True
node_num=1
ans=0
heap=[]
for ed in graph[1]:
    heapq.heappush(heap,ed)

while heap:
    w,nxt=heapq.heappop(heap)
    if vt[nxt]==False:
        vt[nxt]=True
        node_num+=1
        ans+=w
        if node_num==n:
            break
        for wnxt , ng in graph[nxt]:
            if vt[ng]==False:
                heapq.heappush(heap,(wnxt,ng))

if node_num==n:
    print(ans)
else:
    print('orz')
