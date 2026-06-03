n,m,cn,cm=map(int , input().split())
dp=[[0]*(m+1) for _ in range(n+1)]
dp[0][0]=1
marr={(cn,cm),(cn+2,cm+1),(cn+1,cm+2),(cn-1,cm+2),(cn-2,cm+1),(cn-2,cm-1),(cn-1,cm-2),(cn+1,cm-2),(cn+2,cm-1)}
for i in range(n+1):
    for j in range(m+1):
        if (i,j) not in marr:
            if i>0 :dp[i][j]+=dp[i-1][j]
            if j>0 :dp[i][j]+=dp[i][j-1]
print(dp[n][m])