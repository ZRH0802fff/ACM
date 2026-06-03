n=int(input())
arr=list(map(int ,input().split()))
min,max=1001,0
for i  in arr:
    if i<min:
        min = i
    if i>max:
        max=i
print(max-min)