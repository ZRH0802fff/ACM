n=int(input())
book=[[0 for _ in range(n+2)] for _ in range(n+2)]
for i in range(n+2):
    for j in range(n+2):
        if i==0 or j==0 or i==n+1 or j==n+1:
            book[i][j]=-1
h=1
l=(n+1)//2
book[h][l]=1
for i in range(2,n*n+1):
    if h==1 and l!=n:
        h=n
        l+=1
        book[h][l]=i
    elif l==n and h!=1:
        l=1
        h-=1
        book[h][l]=i
    elif h==1 and l==n:
        h+=1
        book[h][l]=i
    else:
        if book[h-1][l+1]==0:
            h-=1
            l+=1
            book[h][l]=i
        else :
            h+=1
            book[h][l]=i
f=[]
for i in book:
    t=" ".join(str(tt) for tt in i[1:n+1])
    f.append(t)
for i in range(1,n+1):
    print(f[i])