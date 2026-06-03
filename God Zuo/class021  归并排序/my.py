import sys

MAXN=100001
arr=[0]*MAXN
helparr=[0]*MAXN
n=0

def merge(l,m,r):
    i=l;a=l;b=m+1
    while a<=m and b<=r:
        if arr[a]<=arr[b]:
            helparr[i]=arr[a]
            a+=1
        else:
            helparr[i]=arr[b]
            b+=1
        i+=1
    while  a<=m:
        helparr[i]=arr[a]
        a+=1;i+=1
    while b<=r:
        helparr[i]=arr[b]
        b+=1 ; i+=1
    for _ in range(l,r+1):
        arr[_]=helparr[_]

#递归版
def merge_sort1(l,r):
    if l==r:
        return
    m=(l+r)//2
    merge_sort1(l,m)
    merge_sort1(m+1,r)
    merge(l,m,r)

def merge_sort2():
    step=1
    while step<n:
        l=0
        while l<n:
            m=l+step-1
            if m+1>=n:
                break
            r=min(n-1,l+(step<<1)-1)
            merge(l,r,m)
            l=r+1
        step<<=1

        

data=sys.stdin.read().split()
index=0
n=int(data[index])
index+=1
for i in range(n):
    arr[i]=int(data[index])
    index+=1
merge_sort2()
print(' '.join(map(str, arr[:n])))