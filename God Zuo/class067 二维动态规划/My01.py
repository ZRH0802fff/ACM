# 测试链接 : https://leetcode.cn/problems/minimum-path-sum/
class Solution:
    def minPathSum(self, grid) -> int:
        n=len(grid)
        m=len(grid[0])
        dp=[[-1] * m for _ in range (n)]
        def f(i,j):
            if i==0 and j==0:
                dp[i][j]=grid[0][0]
            if dp[i][j]!=-1:
                ans= dp[i][j]
            else:
                up=float('inf')
                lf=float('inf')
                if i-1>=0:
                    up=f(i-1,j)
                if j-1>=0:
                    lf=f(i,j-1)
                ans=grid[i][j]+min(up,lf)
            dp[i][j]=ans
            return ans
        return f(n-1,m-1)