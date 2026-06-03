w,x,h=map(int,input().split())
n=int(input())

book=[]
for i in range(w):
    tx=[]
    for j in range(x):
        th=[]
        for k in range(h):
            th.append(True)
        tx.append(th)
    book.append(tx)

for i in range(n):
    x1,y1,z1,x2,y2,z2=map(int,input().split())
    for i in range(x1-1,x2):
        for j in range(y1-1,y2):
            for k in range(z1-1,z2):
                book[i][j][k]=False
total=0
for p in book:
    for r in p:
        for c in r:
            if c==True:
                total+=1
print(total)