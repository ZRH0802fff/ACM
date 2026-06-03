n=int(input())
arr=list(map(int , input().split()))
arr.sort()
total=0
for i in range(1,n-1):
    total+=arr[i]
print(f"{total/(n-2):.2f}")