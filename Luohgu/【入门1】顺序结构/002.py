import sys;
data=list(map(int,sys.stdin.read().split()))
n,q=data[0],data[1]
arr=data[2:2+n]
idx=2+n
for i in range(q):
    op,i,v=data[idx],data[idx+1],data[idx+2]
    idx+=3
    if op==1:
        arr[i-1]+=v
    elif op==2:
        arr[i-1]-=v
print(' '.join(str(i) for i in arr))