class Solution:
    def nthUglyNumber(self, n: int) -> int:
        dp=[0]*(n+1)
        dp[1]=1
        idx1=idx2=idx3=1
        for i in range(2,n+1):
            a=dp[idx1]*2
            b=dp[idx2]*3
            c=dp[idx3]*5
            cur=min(a,b,c)
            if cur==a:
                idx1+=1
            if cur==b:
                idx2+=1
            if cur == c:
                idx3+=1
            dp[i]=cur
        return dp[n]