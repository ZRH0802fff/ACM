import sys
data=list(map(int,sys.stdin.read().split()))
n,c,b=data[0],data[1],data[2]
idx=3
sarr=[0]*n
aarr=[0]*n
for i in range(n):
    sarr[i]=data[idx]
    idx+=1
for i in range(n):
    aarr[i]=data[idx]
    idx+=1
    if aarr[i]>c:
        print(-1)
        exit()
ans=0
for i in range(n):
    b=min(b+sarr[i],c)
    if b<aarr[i]:
        b=min(b+sarr[i] , c)
        ans+=1
    if b<aarr[i]:
        print(-1)
        exit
print(ans)