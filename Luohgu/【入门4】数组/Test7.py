n=int(input())
answer=list(map(int,input().split()))
f=[0,0,0,0,0,0,0,0]
for i in range(n):
    t=list(map(int,input().split()))
    total=0
    for j in t:
        for p in answer:
            if j==p:
                total+=1
                break
    f[7-total]+=1
ff=" ".join(str(t) for t in f[:7])
print(ff)