class Solution:
    def mincostTickets(self, days, costs):
        book=[1,7,30]
        n=len(days)
        dp=[float('inf')]*n
        def f(i):
            if i==n:
                return 0
            if dp[i]!=float('inf'):
                return dp[i]
            ans=float('inf')
            for k in range(3):
                j=i
                while j<n and days[i]+book[k]>days[j]:
                    j+=1
                ans=min(ans,f(j)+costs[k])
            dp[i]=ans
            return ans
        return f(0)