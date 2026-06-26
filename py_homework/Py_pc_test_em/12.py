arr1=tuple(input().split())
arr2=tuple(input().split())
arr=arr1+arr2
ans={}
for ch in arr:
    ans[ch]=ans.get(ch,0)+1
print(arr)
print(ans)