# 测试链接 : https://leetcode.cn/problems/surrounded-regions/
import sys
sys.setrecursionlimit(150000)
class Solution:
    def solve(self, board: list[list[str]]) -> None:
        n,m=len(board),len(board[0])

        def dfs(i,j):
            if i<0 or i==n or j<0 or j==m or board[i][j]!='O':
                return
            board[i][j]='F'
            dfs(i-1,j)
            dfs(i+1,j)
            dfs(i,j-1)
            dfs(i,j+1)
            
        for j in range(m):
            if board[0][j]=='O':
                dfs(0,j)
            if board[n-1][j]=='O':
                dfs(n-1,j)
        for i in range(n):
            if board[i][0]=="O":
                dfs(i,0)
            if board[i][m-1]=='O':
                dfs(i,m-1)
        
        for i in range(n):
            for j in range(m):
                if board[i][j]=='O':
                    board[i][j]='X'
                elif board[i][j]=='F':
                    board[i][j]='O'
