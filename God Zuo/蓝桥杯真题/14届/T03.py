import sys
n,leng=map(int, input().split())
arr=[]
for _ in range(n):
    tarr=list(map(int, sys.stdin.readline().split()))
    arr.append(tarr)

def f(time):
    book=[]
    for i in range(n):
        if arr[i][1]>time:
            continue
        sta,end=arr[i][0]-(time-arr[i][1]),arr[i][0]+(time-arr[i][1])
        if sta<1:
            sta=1
        if end>leng:
            end=leng
        book.append([sta,end])
    book.sort()
    if book[0][0]>1:
        return False
    real=book[0][1]
    for i in range(1,leng(book)):
        if book[i][0]>real+1:
            return False
        real=max(real,book[i][1])
    if real>=leng:
        return True
    return False
  
l,r,ans=0,0,0
for i in range(n):
    if arr[i][1]>r:
        r=arr[i][1]
r+=leng

while l<=r:
    m=(l+r)//2

    if f(m):
        ans=m

        r=m-1
    else:
        l=m+1
print(ans)