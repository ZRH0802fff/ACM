arr=list(map(int ,input().split()))
x=int(input())
x+=30
arr.sort()
for i in range(len(arr)):
    if arr[i]>x:
        print(i)
        exit()
print(10)