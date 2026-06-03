# 测试链接 : https://www.luogu.com.cn/problem/P2330
import sys
data=list(map( int , sys.stdin.read().split()))
n,m=data[0],data[1]
edges=[]
idx=2
for _ in range(m):
    edges.append((data[idx],data[idx+1],data[idx+2]))
    idx+=3
edges.sort(key=lambda x :x[2])
ans=0
father=[_ for _ in range(n+1)]

def find(i):
    while i!=father[i]:
        father[i]=father[father[i]]
        i=father[i] 
    return i

for u,v,w in edges:
    fu=find(u)
    fv=find(v)
    if fu!=fv:
        father[fu]=fv
        ans=w if w>ans else ans

print(n-1,ans)