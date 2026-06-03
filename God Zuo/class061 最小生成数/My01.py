# 测试链接 : https://www.luogu.com.cn/problem/P3366
import sys
data=list(map(int ,sys.stdin.read().split()))
n,m=data[0],data[1]
idx=2
edges=[]
father=[i for i in range(n+1)]
for _ in range(m):
    edges.append((data[idx],data[idx+1],data[idx+2]))
    idx+=3
edges.sort(key=lambda x : x[2])

def find(i):
    while i !=father[i]:
        father[i]=father[father[i]]
        i=father[i] 
    return i
    
ans=0
ed_num=0
for u,v,w in edges:
    fx=find(u)
    fy=find(v)
    if fx!=fy:
        father[fx]=fy
        ans+=w
        ed_num+=1
        if ed_num==n-1:
            break

if ed_num==n-1:
    print(ans)
else:
    print('orz')