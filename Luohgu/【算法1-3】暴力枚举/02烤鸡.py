n=int(input())
count=0
ans=[]
path=[0]*10
if n<10 or n>30:
    print(0)
    exit()

#idx表示到几号调料了，m表示美味程度
def dfs(idx,m):
    global count,path
    if idx==10 :
        if m==n:
            count+=1
            ans.append(path[::])
        return
    for i in range(1,4):
        if m+i<=n:
            path[idx]=i
            dfs(idx+1,m+i)

dfs(0,0)
print(count)
for _ in ans:
    print(' '.join(str(i) for i in _))
