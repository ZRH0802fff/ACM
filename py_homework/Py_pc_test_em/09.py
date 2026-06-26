arr=list(map(int,input().split()))
ans=[]
for num in arr:
    if num  not in ans:
        ans.append(num)
print(ans)