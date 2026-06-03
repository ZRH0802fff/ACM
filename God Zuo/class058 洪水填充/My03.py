# 测试链接 : https://leetcode.cn/problems/making-a-large-island/
import sys
sys.setrecursionlimit(250000)
class Solution:
    def largestIsland(self, grid: list[list[int]]) -> int:
        n=len(grid)
        size={0:0}
        id=2
        ans=0

        def dfs(i,j,id):
            if i<0 or j<0 or i==n or j==n or grid[i][j]!=1:
                return 0
            grid[i][j]=id
            return 1+dfs(i-1,j,id)+dfs(i+1,j ,id)+dfs(i,j-1,id)+dfs(i,j+1,id)
        
        for i in range(n):
            for j in range(n):
                if grid[i][j]==1:
                    ts=dfs(i,j,id)
                    size[id]=ts
                    id+=1
                    ans=max(ans,ts)

        for i in range(n):
            for j in range(n):
                if grid[i][j]==0:
                    ng_id=set()
                    if i>0 : ng_id.add(grid[i-1][j])
                    if i<n-1 : ng_id.add(grid[i+1][j])
                    if j>0: ng_id.add(grid[i][j-1])
                    if j<n-1: ng_id.add(grid[i][j+1])

                    merge_size=1+sum(size[_] for _ in ng_id)
                    ans =merge_size if merge_size>ans else ans
        return ans