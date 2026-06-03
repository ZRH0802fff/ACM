arr=[]
for _ in range(7):
    n1,n2=map(int,input().split())
    n=n1+n2
    arr.append(n)
mn=max(arr)
if mn>8:
    for i in range(7):
        if arr[i]==mn:
            print(i+1)
            break
else:
    print(0)