# 测试链接 : https://www.luogu.com.cn/problem/U107394
import sys
import heapq
MAXN=100005
MAXM=100005
head=[0]*MAXN
nxt=[0]*MAXM
to=[0]*MAXM
cnt=1
indegree=[0]*MAXN
ans=[0]*MAXN

def bulid(n):
    global cnt
    cnt=1
    for i in range(1,n+1):
        head[i]=0
        indegree[i]=0

def add_edge(f,t):
    global cnt
    nxt[cnt]=head[f]
    to[cnt]=t
    head[f]=cnt
    cnt+=1

def solve(n):
    heap=[]
    for i in range(1,n+1):
        if indegree[i]==0:
            heapq.heappush(heap,i)
    fill=0
    while heap:
        cur=heapq.heappop(heap)
        ans[fill]=cur
        fill+=1

        ei=head[cur]
        while ei !=0:
            v=to[ei]
            indegree[v]-=1
            if indegree[v]==0:
                heapq.heappush(heap,v)
            ei=nxt[ei]

data=sys.stdin.read().split()
idx=0
while idx<len(data):
    n=int(data[idx])
    m=int(data[idx+1])
    idx+=2
    bulid(n)
    for _ in range(m):
        f=int(data[idx])
        t=int(data[idx+1])
        idx+=2
        add_edge(f,t)
        indegree[t]+=1
    solve(n)
    sys.stdout.write(" ".join(map(str, ans[:n])) + "\n")