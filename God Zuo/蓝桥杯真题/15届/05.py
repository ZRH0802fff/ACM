import sys
n=int(input())
arr1=list(map(int, sys.stdin.readline().split()))
arr2=list(map(int, sys.stdin.readline().split()))

def f(n):
    if n == 0: return n 
    num=n
    tarr=set()
    while num>0:
        t=num%10
        if t == 0 or t == 2 or t == 4:
            tarr.add(t)
        num//=10
    if not tarr:
        return [False]
    return list(tarr)



arr1 = [f(x) for x in arr1]
arr2 = [f(x) for x in arr2]
flar=True
idx=0
yao=[]
while idx<n:
    if flar:
        if arr1[idx][0]:
            idx+=1

        yao=arr1[idx][:]