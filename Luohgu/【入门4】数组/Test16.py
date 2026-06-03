n=int(input())
book=[[1],[1,1]]
if n==1:
    print(1)
    exit(0)
if n==2:
    print(1)
    print(1,1)
    exit(0)
for i in range(2,n):
    t=[1]
    for j in range(1,i):
        t.append(book[i-1][j-1]+book[i-1][j])
    t.append(1)
    book.append(t)
for i in book:
    print(" ".join(str(x) for x in i ))