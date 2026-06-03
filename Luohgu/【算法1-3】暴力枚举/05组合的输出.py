n,r=map(int ,input().split())
path=[]
ans=[]
def dfs(con,i):
    if con==r:
        ans.append(''.join( f"{n:3d}" for n in path))
        return
    if i==n+1:
        return
    dfs(con,i+1)
    path.append(i)
    dfs(con+1,i+1)
    path.pop()

dfs(0,1)
ans.sort()
for ch in ans:
    print(ch)