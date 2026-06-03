n=int(input())
path=[]
ans=[]
used=[False]*(n+1)
def dfs(i):
    if i==n :
        ans.append(''.join(f"{x:5d}"for x in path))
        return
    for num in range(1,n+1):
        if not used[num]:
            used[num]=True
            path.append(num)
            dfs(i+1)
            used[num]=False
            path.pop()
dfs(0)
for _ in ans:
    print(_)