n=10
ans=set()
book=[0,5,5,10,10,15,15,20,20,25,25]
def dfs(i,tans):
    if i==n+1:
        ans.add(tans)
        return
    dfs(i+1,tans+book[i])
    dfs(i+1,tans)

dfs(0,0)
ans=list(ans)
ans.sort()
print(ans)
print(len(ans))

    