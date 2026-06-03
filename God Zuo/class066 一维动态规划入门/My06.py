# 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        n=len(s)
        dp=[0]*n
        ans=0
        for i in range(1,n):
            if s[i]==")":
                p=i-dp[i-1]-1
                if p>=0 and s[p]=="(":
                    dp[i]=dp[i-1]+2+dp[p-1]
            ans=max(ans,dp[i])
        return ans