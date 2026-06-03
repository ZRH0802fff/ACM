l=int(input())
dp=[0]*(l+1)
for i in range(1,l+1):
    for j in range(i,l+1,i):
        dp[j]+=1
s=[0]*(l+1)
for i in range(l+1):
    s[i]+=s[i-1]+dp[i]
ans=0
for i in range(1,l):
    ans+=dp[i]*s[l-i]
print(ans)