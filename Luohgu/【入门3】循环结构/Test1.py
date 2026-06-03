n=int(input())
num=list(map(int ,input().split()))
min=1001
for i in num:
    if i<min :
        min =i
print(min)