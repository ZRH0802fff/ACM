import sys 
sys.setrecursionlimit(200000)
data=list(map(int,sys.stdin.read().split()))
n,m=data[0],data[1]
father=list(range(n+1))
size=[1]*(n+1)
huan=[]

def find(i):
    if i!=father[i]:
        father[i]=find(father[i])
    return father[i]

for i in range(2,m*2+2,2):
    u,v=data[i],data[i+1]
    fu=find(u)
    fv=find(v)
    if fu==fv:
        huan.append((u,v))
    else:
        father[fu]=fv
        size[fv]+=size[fu]
forest={}
for i in range(1,n+1):
    if i==father[i]:
        forest[i]=True
for u,v in huan:
    fa=find(u)
    if forest[fa]:
        ans+=1
        forest[fa]=False
    else:
        ans-=1

print(forest)
print(huan)
print(father)
print(size)