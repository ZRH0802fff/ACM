import sys 
data=map(int , sys.stdin.read().split())
arr=[0]*10000005
n=data[0]
m=data[1]
idx=2

def set(l,r,s,e,d):
    arr[l]+=s
    arr[l+1]+=d-s
    arr[r+1]-=d+e
    arr[r+2]+=e

def build1(n):
    for i in range(1,n+1):
        arr[i]+=arr[i-1]
    for i in range(1,n+1):
        arr[i]+=arr[i-1]    


for i in range(m):
    l=data[idx];idx+=1
    r=data[idx];idx+=1
    s=data[idx];idx+=1
    e=data[idx];idx+=1
    if r-l==0:
        d=0
    else:
        d=(e-s)//(r-l)
    set(l,r,s,e,d)
build1(n)
su,ma=0,0
for i in range(1,n+1):
    ma=max(ma,arr[i])
    su^=arr[i]
print(f"{sum} {max}")




