# dp=[0]*15
# dp[1]=1
# dp[2]=2
# dp[3]=5
# for i in range(4,14):
#     dp[i]=dp[i-1]+dp[i-2]+dp[i-3]*4
# for i in range(14):
#     print(f"{i} : {dp[i]}")

n=int(input())
f=[0]*(n+1)
g=[0]*(n+1)
MOD=10000
f[0],g[0],f[1],g[1]=1,0,1,1
for i in range(2,n+1):
    f[i]=((f[i-1]+f[i-2])%MOD+2*g[i-2]%MOD)%MOD
    g[i]=(g[i-1]+f[i-1])%MOD
print(f[n])