n=int(input())
book=[False]*2000001
for i in range(n):
    a,t=input().split()
    a=float(a);t=int(t)
    for j in range(1,t+1):
        idx=int(a*j)
        book[idx]=not book[idx]
index=0
for i in book:
    if i:
        print(index)
        break
    index+=1