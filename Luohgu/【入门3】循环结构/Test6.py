n,x=map(int,input().split())
count=0
m=str(x)
for i in range(1,n+1):
    for j in str(i):
        if j==m:
            count+=1
print(count)