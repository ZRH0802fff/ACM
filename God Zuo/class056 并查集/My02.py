# 测试链接 : https://www.luogu.com.cn/problem/P3367
import sys
sys.setrecursionlimit(300000)
data=sys.stdin.read().split()
n,m=int(data[0]),int(data[1])
idx=2
father=[i for i in range(n+1)]


def find(i):
    if i!=father[i]:
        father[i]=find(father[i])
    return father[i]

def issameset(x,y):
    return find(x)==find(y)

def union(x,y):
    father[find(x)]=find(y)

out=[]
for _ in range(m):
    opt,x,y=data[idx],int(data[idx+1]),int(data[idx+2])
    idx+=3
    if opt=='1':
        union(x,y)
    else:
        out.append('Y' if issameset(x,y) else 'N')
sys.stdout.write('\n'.join(out)+'\n')
