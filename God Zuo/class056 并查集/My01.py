# 测试链接 : https://www.nowcoder.com/practice/e7ed657974934a30b2010046536a5372
import sys
data=list(map(int ,sys.stdin.read().split()))
n,m=data[0],data[1]
idx=2
father=[i for i in range(n+1)]
size=[1]*(n+1)
def find(i):
    path=[]
    while i !=father[i]:
        path.append(i)
        i=father[i]
    for cur in path:
        father[cur]=i
    return i

def union(x,y):
    fx=find(x)
    fy=find(y)
    if fx != fy:
        if size[fx]>=size[fy]:
            father[fy]=fx
            size[fx]+=size[fy]
        else:
            father[fx]=fy
            size[fy]+=size[fx]

out=[]
for _ in range(m):
    opt,x,y=data[idx],data[idx+1],data[idx+2]
    idx+=3
    if opt==1:
        out.append("Yes" if find(x) == find(y) else "No")
    else:
        union(x,y)

print('\n'.join(_ for _ in out))