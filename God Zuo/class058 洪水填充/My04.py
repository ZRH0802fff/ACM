# 测试链接 : https://leetcode.cn/problems/bricks-falling-when-hit/
import sys
sys.setrecursionlimit(250000)
class Solution:
    def hitBricks(self, grid: list[list[int]], hits: list[list[int]]) -> list[int]:
        n,m=len(grid),len(grid[0])
        ans=[0]*len(hits)
        for r,c in hits:
            grid[r][c]-=1
        
        def dfs(i,j):
            if i<0 or j<0 or i==n or j == m or grid[i][j]!=1:
                return 0
            grid[i][j]=2
            return 1+dfs(i-1,j)+dfs(i,j-1)+dfs(i+1,j)+dfs(i,j+1)
        
        def worth(i,j):
            return grid[i][j]==1 and (i==0 or (i>0 and grid[i-1][j]==2) 
                                           or (i<n-1 and grid[i+1][j]==2)
                                           or (j>0 and grid[i][j-1]==2 ) 
                                           or (j<m-1 and grid[i][j+1]==2))

        for j in range(m):
            dfs(0,j)
        
        for i in range(len(hits)-1,-1,-1):
            r,c = hits[i]
            grid[r][c]+=1
            if worth(r,c):
                ans[i]=dfs(r,c)-1
        
        return ans
