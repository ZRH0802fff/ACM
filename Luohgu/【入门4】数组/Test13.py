n,m,p=map(int,input().split())
ma=n+m+p
book=[0]*(ma+1)
for i in range(1,n+1):
    for j in range(1,m+1):
        for k in range(1,p+1):
            t=i+j+k
            book[t]+=1
            print(i,j,k,t)
print(book)
f=0
index=0
for i in book:
    if i>f:
       f=i
       ff=index
    index+=1
print(ff)
