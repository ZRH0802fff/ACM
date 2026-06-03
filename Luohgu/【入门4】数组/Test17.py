n,m,k=map(int , input().split())
book = [[0 for _ in range(n+4)] for _ in range(n+4)] 
#print(book)
for i in range (n+4):
    for j in range(n+4):
        if i==0 or i==1 or j==0 or j==1 or i==n+3 or i==n+2 or j==n+3 or j==n+2:
            book[i][j]=-1
            #print(i,j)
#print(book)
for i in range(m):
    x,y=map(int ,input().split())
    for i in range(x-1,x+4):
        if book[i][y+1]!=-1:
            book[i][y+1]=1
    for i in range(y-1,y+4):
        if book[x+1][i]!=-1:
            book[x+1][i]=1
    if x!=-1 and y!=-1:
        book[x][y]=1
    if x+2!=-1 and y!=-1:
        book[x+2][y]=1
    if x!=-1 and y+2!=-1:
        book[x][y+2]=1
    if x+2!=-1 and y+2!=-1:
        book[x+2][y+2]=1
if k!=0:
    for i in range(k):
        x,y=map(int ,input().split())
        for i in range(x-1,x+4):
            for j in range(y-1,y+4):
                if book[i][j]!=-1:
                    book[i][j]=1
total=0
for row in book:
    for ge in row:
        if ge==0:
            total+=1
print(total)