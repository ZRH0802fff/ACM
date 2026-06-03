W,w,m=map(int,input().split())
w=float(w)
W=float(W)
l,r=0.0,3.0

def ok(num):
    balance=W
    for _ in range(m):
        balance=balance*(1+num)-w
    return balance<=0

for _ in range(100):
    mid=(l+r)/2.0
    if ok(mid):
        l=mid
    else:
        r=mid
ans=l*100
print(f'{ans:.1f}')
