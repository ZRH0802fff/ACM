class Solution:
    def numDecodings(self, s: str) -> int:
        n=len(s)
        dp=[-1]*n
        def f(i):
            if i==n:
                return 1
            if dp[i]!=-1:
                return dp[i]
            if s[i]=='0':
                ans=0
            else:
                ans=f(i+1)
                if i+1<n and int(s[i:i+2])<27:
                    ans+=f(i+2)
            dp[i]=ans
            return ans
        return f(0)
    def numDecodings2(self, s: str) -> int:
        n=len(s)
        dp=[0]*(n+1)
        dp[n]=0
        