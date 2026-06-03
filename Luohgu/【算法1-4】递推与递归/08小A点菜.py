"""
暴力递归解法

import sys
sys.setrecursionlimit(2000000)
data=list(map(int,sys.stdin.read().split()))
n,m=data[0],data[1]
aaa=[False]*n
book=data[2:]
ans=0

def dfs(i):
    global ans
    if i==n:
        sum=0
        for i in range(n):
            if aaa[i]==True:sum+=book[i]
        if sum==m : ans+=1
        return
    dfs(i+1)
    aaa[i]=True
    dfs(i+1)
    aaa[i]=False

dfs(0)
print(ans)

"""

#动态规划解法
#二维解      dp[i][j]表示只考虑签i种菜的情况下，刚好花光j元钱的方案数

import sys
sys.setrecursionlimit(2000000)
data=list(map(int,sys.stdin.read().split()))
n,m=data[0],data[1]
book=data[2:]
dp=[[0]*(m+1) for _ in range(n+1)]
dp[0][0]=1
for i in range(1,n+1):
    w=book[i-1]
    for j in range(m+1):
        dp[i][j]=dp[i-1][j]
        if j>=w: dp[i][j]+=dp[i-1][j-w]

print(dp[n][m])
