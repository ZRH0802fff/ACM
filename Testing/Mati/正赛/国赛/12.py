import sys;
data=list(map(int,sys.stdin.read().split()))
n=data[0]
k=data[1]
ed=n//k*k
idx=k
ans=0
while idx!=k:
    ans+=data[idx+1]
    idx*=k
print(idx)