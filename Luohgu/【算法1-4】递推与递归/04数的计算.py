n=int(input())
dp=[0]*1010
dp[1]=1
dp[2]=2
for i in range(3,n+1):
    if i%2==0:dp[i]=dp[i-1]+dp[i//2]
    else:dp[i]=dp[i-1]
print(dp[n])