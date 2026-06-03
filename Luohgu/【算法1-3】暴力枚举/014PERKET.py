import sys
data=list(map(int ,sys.stdin.read().split()))
n=data[0]
book=[[0,0] for _ in range(n)]
idx=1
for i in range(n):
    book[i][0],book[i][1]=data[idx],data[idx+1]
    idx+=2
aaa=[False]*n
ans=float('inf')
path=[]
def dfs(i):
    global ans,path
    if i==n:
        if path==[]:
            return
        cheng,jia=1,0
        for i in path:
            cheng*=book[i][0]
            jia+=book[i][1]
        t=abs(cheng-jia)
        ans=t if ans>t else ans
        return
    # print(i,aaa[i])
    dfs(i+1)
    path.append(i)
    dfs(i+1)
    path.pop()
    

dfs(0)
print(ans)
# print(aaa)