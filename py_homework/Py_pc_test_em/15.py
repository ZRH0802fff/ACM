n=int(input())
arr={}
for _ in range(n):
    k,v=input().split()
    v=int(v)
    arr[k]=v
for k,v in arr.items():
    if v>=60:
        print(k)