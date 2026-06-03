# 测试链接 : https://leetcode.cn/problems/largest-1-bordered-square/
from typing import List

class Solution:
    def largest1BorderedSquare(self, grid: List[List[int]]) -> int:
        n=len(grid)
        m=len(grid[0])

        def get_val(i,j):
            return 0 if i<0 or j<0 else grid[i][j]
        
        def get_sum(a,b,c,d):
            if a>c or b>d:
                return 0
            return grid[c][d]-get_val(c,b-1)-get_val(a-1,d)+get_val(a-1,b-1)
        
        for i in range(n):
            for j in range(m):
                grid[i][j]+=get_val(i,j-1)+get_val(i-1,j)-get_val(i-1,j-1)
        if get_sum(0,0,n-1,m-1)==0:
            return 0
        ans=1
        for a in range(n):
            for b in range(m):
                c,d,k=a+ans,b+ans,ans+1
                while c<n and d<m:
                    if get_sum(a,b,c,d)-get_sum(a+1,b+1,c-1,d-1)==(k-1)<<2:
                        ans=k
                    c+=1
                    d+=1
                    k+=1
        return ans*ans

     