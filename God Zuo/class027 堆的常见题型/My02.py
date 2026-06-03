import sys
import heapq

MAXN=10001
line= [[0,0] for _ in range(MAXN)]
n=0
heap=[]

def compute():
    global line , n , heap
    heap=[]
    line[:n] = sorted(line[:n], key=lambda x: x[0])
    ans=0
    for i in range(n):
        while heap and line[i][0]>=heap[0]:
            heapq.heappop(heap)
        heapq.heappush(heap,line[i][1])
        ans=max(ans,len(heap))
    return ans