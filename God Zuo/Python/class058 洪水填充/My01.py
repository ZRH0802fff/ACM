# 测试链接 : https://leetcode.cn/problems/number-of-islands/
import sys
sys.setrecursionlimit(15000)
class Solution:
    def numIslands(self, grid: list[list[str]]) -> int:
        n=len(grid)
        m=len(grid[0])
        ans=0
        
        def dfs(i,j):
            if i<0 or j < 0 or j==m or i == n or grid[i][j]!='1':
                return
            grid[i][j]='0'
            dfs(i-1,j)
            dfs(i+1,j)
            dfs(i,j-1)
            dfs(i,j+1)

        for i in range(n):
            for j in range(m):
                if grid[i][j]=='1':
                    ans+=1
                    dfs(i,j)
        return ans