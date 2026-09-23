import sys;
data=list(map(int,sys.stdin.read().split()))

T=data[0]
idx=1
for _ in range(T):
    n=data[idx]
    idx+=1


    arr=[0]*n
    shu=[0]*n
    heng=[0]*n
    tou=data[idx]
    sd=[0]*n
    hd=[0]*n

    arr[0]=data[idx]
    shu[0]=data[idx]*(n-2)
    heng[0]=data[idx]*(n-2)
    idx+=1
    if(n==1) :
        print(tou)
        continue
    
    for i in range(1,n):
        arr[i]=data[idx]
        idx+=1

        shu[i]=arr[i]*(n-i)
        heng[n-i]=arr[i]*i
        if i>2:
            sd[i]=sd[i-1]+arr[i-2]
    
    arrh=[0]*n
    arrh[0]=tou
    for i in range(1,n):arrh[i]=arr[n-i]
    
    
    for i in range(3,n):
        hd[i]=hd[i-1]+arrh[i-2]
   
    # print(arr)
    # print(arrh)
    # print(shu)
    # print(heng)
    # print(sd)
    # print(hd)

    ans=heng[0]+heng[1]
    for i in range(2,n):
        t=heng[i]+heng[i-1]+hd[i]*2
        if t<ans: ans=t

    t=shu[0]+shu[1]
    if t<ans: ans=t
    for i in range(2,n):
        t=shu[i]+shu[i-1]+sd[i]*2
        if t<ans :ans=t

    ans+=tou*2
    print(ans)
