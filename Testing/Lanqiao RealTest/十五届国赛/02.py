import sys
sys.setrecursionlimit(200000)
n=2024
gys=set()

def dfs(i,tans):
    if i==6 :
        gys.add(tans)
        return
    dfs(i+1,tans)
    dfs(i+1,tans*i)

dfs(0,1)
tt=list(gys)
tt.sort()
print(tt)