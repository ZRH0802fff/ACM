import sys
data=list(map(int,sys.stdin.read().split()))
n=data[0]
arr=[[0,0] for _ in range(n)]
idx=1
for i in range(n):
    arr[i][0],arr[i][1]=data[idx],data[idx+1]
    idx+=2
arr.sort(key=lambda x :x[0])
sta=arr[0][0]
ed=arr[0][1]
ans=0