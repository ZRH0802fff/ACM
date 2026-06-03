#https://leetcode.cn/problems/as-far-from-land-as-possible/description/
class Solution:
    def maxDistance(self, grid: list[list[int]]) -> int:
        n,m=len(grid),len(grid[0])
        queue=[(0,0)]*(n*m)
        l,r,level,sea=0,0,0,0
        for i in range(n):
            for j in range(m):
                if grid[i][j]==1:
                    queue[r]=(i,j)
                    r+=1
                else:
                    sea+=1
        if sea==0 or sea == n*m:
            return -1
        move={(-1,0),(1,0),(0,-1),(0,1)}
        while l<r:
            level+=1
            size=r-l
            for _ in range(size):
                x,y=queue[l]
                l+=1
                for dx,dy in move:
                    tx=dx+x
                    ty=dy+y
                    if  0<=tx<n and 0<=ty<n and grid[tx][ty]==0:
                        queue[r]=(tx,ty)
                        r+=1
                        grid[tx][ty]=2
        return level-1
