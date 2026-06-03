n=int(input())
bk=[]
for i in range(n):
    t=input().split()
    bk.append(t)

for p in bk:
    p[1]=int(p[1])
    p[2]=int(p[2])
    p[3]=int(p[3])

def f(p1,p2):
    t1=abs(bk[p1][1]-bk[p2][1])
    t2=abs(bk[p1][2]-bk[p2][2])
    t3=abs(bk[p1][3]-bk[p2][3])
    t=abs(bk[p1][1]+bk[p1][2]+bk[p1][3]-bk[p2][1]-bk[p2][2]-bk[p2][3])
    return t1<=5 and t2<=5 and t3<=5 and t<=10

for i in range(n):
    for j in range(i+1,n):
        if f(i,j):
            print(bk[i][0]+' '+bk[j][0])