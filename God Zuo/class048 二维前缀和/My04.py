#测试链接 : https://leetcode.cn/problems/stamping-the-grid/
from typing import List

class Solution:
    def possibleToStamp(self, grid: List[List[int]], stampHeight: int, stampWidth: int) -> bool:
        n=len(grid)
        m=len(grid[0])
        sum_book=[[0]*(m+1) for _ in range (n+1)]
        for i in range(n):
            for j in range(m):
                sum_book[i+1][j+1]=grid[i][j]+sum_book[i][j+1]+sum_book[i+1][j]-sum_book[i][j]
        cfen_book=[[0]*(m+2) for _ in range(n+2)]
        for a in range(1,n-stampHeight+2):
            c=a+stampHeight-1
            for b in range(1,m-stampWidth+2):
                d=b+stampWidth-1
                sum=sum_book[c][d]-sum_book[c][b-1]-sum_book[a-1][d]+sum_book[a-1][b-1]
                if sum==0:
                    cfen_book[a][b]+=1
                    cfen_book[a][d+1]-=1
                    cfen_book[c+1][b]-=1
                    cfen_book[c+1][d+1]+=1

        for i in range(1,n+1):
            for j in range(1,m+1):
                cfen_book[i][j]+=cfen_book[i-1][j]+cfen_book[i][j-1]-cfen_book[i-1][j-1]
                if grid[i-1][j-1]==0 and cfen_book[i][j]==0:
                    return False
        return True