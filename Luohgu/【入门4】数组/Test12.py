n,m=map(int,input().split())
arr=[]
for i in range(n):
    t=int(input())
    arr.append(t)
min=300000
if m==n:
    sum=0
    for i in arr:
        sum+=i
    print(sum)
    exit(0)
if m==n-1:
    sum1,sum2=0,0
    for i in range(n-1):
        sum1+=arr[i]
    for i in range(1,n):
        sum2+=arr[i]
    if sum1<sum2:
        print(sum1)
    else:
        print(sum2)
    exit(0)
for i in range(n-m-1):
    t=0
    for j in range(i,i+m):
        t+=arr[j]
    if min>t:
        min=t
print(min)