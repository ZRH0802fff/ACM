l,n=map(int,input().split())
book=[]
for i in range(l+1):
    book.append(1)
for i in range(n):
    start,end=map(int ,input().split())
    for j in range(start,end+1):
        book[j]=0
total=0
for i in book:
    if i==1:
        total+=1
print(total)