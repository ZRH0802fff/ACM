import sys
data=list(map(int,sys.stdin.read().split()))
n,m=data[0],data[1]
book=data[2:]
idx=2+n
out=[]
for _ in range(m):
    num=data[idx]
    idx+=1
    l,r=0,n-1
    ans=0
    flag=False
    while l<r:
        mid=(l+r)//2
        if book[mid]==num:
            while book[mid]==num:
                mid-=1
            out.append(mid+2)
            flag=True
            break
        elif book[mid]>num:
            r=mid-1
        else:
            l=mid+1
    if flag==False :
        out.append(-1)
sys.stdout.write(' '.join(str(_) for _ in out))