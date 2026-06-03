n=int(input())
book=[[0]*n for i in range(n) ]
ce=0
num=1
while ce<=n//2:
    for i in range(ce,n-ce):
        book[ce][i]=num
        num+=1
    for i in range(ce+1,n-ce):
        book[i][n-ce-1]=num
        num+=1
    for i in range(n-ce-2,ce-1,-1):
        book[n-ce-1][i]=num
        num+=1
    for i in range(n-ce-2,ce,-1):
        book[i][ce]=num
        num+=1 
    ce+=1
for i in book:
    print("".join(f"{x:3}"for x in i)) 