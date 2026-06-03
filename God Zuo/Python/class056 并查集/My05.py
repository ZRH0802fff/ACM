# 测试链接 : https://leetcode.cn/problems/number-of-islands/
class Solution:
    def numIslands(self, grid: list[list[str]]) -> int:
        n=len(grid)
        m=len(grid[0])
        father=list(range(n*m))
        sets=0
        for i in range(n):
            for j in range(m):
                if grid[i][j]=='1':
                    sets+=1
        
        def find(i):
            if i !=father[i]:
                father[i]=find(father[i])
            return father[i]
        
        def union(r1,c1,r2,c2):
            nonlocal sets
            fx=find(r1*m+c1)
            fy=find(r2*m+c2)
            if fx!=fy:
                father[fx]=fy
                sets-=1
            
        for i in range(n):
            for j in range(m):
                if grid[i][j]=='1':
                    if j>0 and grid[i][j-1]=='1':
                        union(i,j,i,j-1)
                    if i>0 and grid[i-1][j]=='1':
                        union(i,j,i-1,j)
        return sets