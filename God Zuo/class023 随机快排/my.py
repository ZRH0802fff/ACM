import sys
import random

MAXN=100001
arr=[0]*MAXN
n=0
first=0
last=0

def swap(i,j):
    arr[i],arr[j]=arr[j],arr[i]

def quicksort1(l,r):
    if l>=r:
        return
    x=arr[random.randint(l, r)]
    mid=partition1(l,r,x)
    quicksort1(l,mid-1)
    quicksort1(mid+1,r)

def partition1(l,r,x):
    a=l
    xi=0
    for i in range(l,r+1):
        if arr[i]<=x:
            swap(i,a)
            if arr[a]==x:
                xi=a
            a+=1
    swap(xi,a-1)
    return a-1

def quicksort2(l,r):
    if l>=r:
        return
    x=arr[random.randint(l,r)]
    partition2(l,r,x)
    left=first
    right=last
    quicksort2(l,left-1)
    quicksort2(right+1,r)

def partition2(l,r,x):
    global first,last
    first=l
    last=r
    i=l
    while i<=last:
        if arr[i]<x:
            swap(first,i)
            i+=1
            first+=1
        elif arr[i]==x:
            i+=1
        else:
            swap(last,i)
            last-=1

data=sys.stdin.read().split()
idx=0
n=int(data[idx])
idx+=1
for i in range(n):
    arr[i]=int(data[idx])
    idx+=1
quicksort2(0,n-1)
print(" ".join(str(arr[i]) for i in range(n)))