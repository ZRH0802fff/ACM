s=list(input())
for i , ch in enumerate(s) :
    s[i]=ord(ch)-ord('a')+1
def f():
    if len(s)==1:
        return s[0]
    dp=[0]*len(s)
    dp[0]=s[0]
    dp[1]=max(dp[0],s[1])
    for i in range(2,len(s)):
        dp[i]=max(dp[i-1],dp[i-2]+s[i])
    return(dp[-1])

print(f())