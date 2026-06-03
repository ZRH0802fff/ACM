import sys
data=list(map(int,sys.stdin.read().split()))
L,n,m=data[0],data[1],data[2]

if n==0 or m==n:
    print(L)
    exit()

oparr=[0]*n
oparr[0]=data[3]
idx=4
for i in range(1,n):
    oparr[i]=data[idx]-data[idx-1]
    idx+=1
oparr.append(L-data[-1])
n+=1

if m==0:
    print(min(oparr))
    exit()

l,r,ans=1,L,0
#print(oparr)
beifen=oparr[:]
def ok(num):
    global oparr
    ans=0
    for i in range(n):
        if oparr[i]<num:
            #print(f'in OK function,indxe={i},oparr[i]={oparr[i]}<num={num}')
            #print(oparr)
            if i+1<n:
                oparr[i+1]+=oparr[i]
            ans+=1
    oparr=beifen[:]
    return ans<=m

while l<=r:
    mid=(l+r)//2
    if ok(mid):
        #print(mid,1)
        l=mid+1
        ans=mid if mid>ans else ans
    else:
        #print(mid,2)
        r=mid-1

print(ans)