n,m=map(int,input().split())
pre2=1
pre1=1
cur=2
for i in range(3,m-n+2):
    cur=pre1+pre2
    pre2=pre1
    pre1=cur
print(cur)