import sys 
input = lambda: sys.stdin.readline().strip()
n, q = map(int, input().split())
arr = list(map(int, input().split()))
arr.sort()
sta=0
ans=sum(arr)
for _ in range(q):
    a=int(input())
    if a==1 or ans==0:
        print(ans)
        continue
    t=0
    for i in range(sta,n):
        arr[i]//=a
        if arr[i]==0:
            sta=i
        else:
            t+=arr[i]
    ans=t
    print(t)