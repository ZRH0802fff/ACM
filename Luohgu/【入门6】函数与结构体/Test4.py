n,m=map(int,input().split())
ma=[]
for i in range(n):
    t=list(map(int,input().split()))
    t.sort()
    sum=0
    for ch in t[1:m-1]:
        sum+=ch
    print(sum)
    ma.append(sum/(m-2))
print(f"{max(ma):.2f}")