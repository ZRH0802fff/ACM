import sys
data=list(map(int,sys.stdin.read().split()))
n,m=data[0],data[1]
idx=2
arr1=[[0]*n for _ in range(n)]
arr2=[[0]*m for _ in range(m)]
MOD=1000000007
for i in range(n):
    for j in range(n):
        arr1[i][j]=data[idx]
        idx+=1
for i in range(m):
    for j in range(m):
        arr2[i][j]=data[idx]
        idx+=1
ans=0
for i in range(n-m+1):
    for j in range(n-m+1):
        for k in range(m):
            for l in range(m):
                #print(i+k,j+l,k,l)
                ans+=(arr1[i+k][j+l]^arr2[k][l])%MOD
print(ans)