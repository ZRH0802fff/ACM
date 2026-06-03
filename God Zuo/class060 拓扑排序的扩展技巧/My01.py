# 测试链接 : https://www.luogu.com.cn/problem/P4017
import sys
from collections import deque
ia=iter(list(map(int,sys.stdin.read().split())))
MOD=80112002
while True:
    try:
        n=next(ia)
    except StopIteration:
        break
    n=n
    m=next(ia)
    head=[0]*(n+1)
    nxt=[0]*(m+1)
    to=[0]*(m+1)
    lines=[0]*(n+1)
    indegree=[0]*(n+1)
    cnt=1
    for i in range(m):
        u=next(ia)
        v=next(ia)

        nxt[cnt]=head[u]
        to[cnt]=v
        head[u]=cnt
        indegree[v]+=1
        cnt+=1

    queue=deque()
    for i in range(1,n+1):
        if indegree[i]==0:
            queue.append(i)
            lines[i]=1
    
    ans=0
    while queue:
        u=queue.popleft()
        if head[u]==0:
            ans=(ans+lines[u])%MOD
        else:
            ei=head[u]
            while ei !=0:
                v=to[ei]
                lines[v]=(lines[u]+lines[v])%MOD
                indegree[v]-=1
                if indegree[v]==0:
                    queue.append(v)
                ei=nxt[ei]
    print(ans)

        