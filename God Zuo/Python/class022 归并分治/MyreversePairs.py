import sys

MAXN=100001
arr=[0]*MAXN
help=[0]*MAXN

def counts(l,r):
    if l==r:
        return 0 
    m=(l+r)//2
    return counts(l,m)+counts(m+1,r)+merge(l,m,r)

def merge(l,m,r):

    ans=0
    j=m+1
    for i in range(l,m+1):
        while j<=r and arr[i]>arr[j]*2 :
            j+=1
        ans+=j-m-1

    i=l
    a=l
    b=m+1
    while a<=m and b<=r:
        if arr[a]<=arr[b]:
            help[i]=arr[a]
            a+=1
        else:
            help[i]=arr[b]
            b+=1
        i+=1
    while a<=m:
        help[i]=arr[a]
        a+=1
        i+=1
    while b<=r:
        help[i]=arr[b]
        b+=1
        i+=1

    for _ in range(l,r+1):
        arr[_]=help[_]
    return ans