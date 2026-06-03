import sys

# 解除递归封印，防止极端情况（比如全屏蛇形 O）爆栈
sys.setrecursionlimit(150000)

class Solution:
    def solve(self, board: list[list[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        if not board or not board[0]:
            return
            
        n = len(board)
        m = len(board[0])
        
        # 内嵌 DFS，闭包特性可以直接读写外层的 board
        def dfs(i: int, j: int):
            # 越界，或者不是 'O'（可能是 'X' 或已经被标记为 'F'），直接返回
            if i < 0 or i == n or j < 0 or j == m or board[i][j] != 'O':
                return
                
            # 发放免死金牌！把与边界连通的 'O' 临时标记为 'F'
            board[i][j] = 'F'
            
            # 洪水填充：上下左右蔓延
            dfs(i + 1, j)
            dfs(i - 1, j)
            dfs(i, j + 1)
            dfs(i, j - 1)
            
        # 第一阶段：沿着棋盘四周的【边界】巡逻，派出 DFS
        # 1. 搜上下两行
        for j in range(m):
            if board[0][j] == 'O': dfs(0, j)
            if board[n - 1][j] == 'O': dfs(n - 1, j)
            
        # 2. 搜左右两列 (避开四个角，其实重复搜也不影响，但这样更严谨)
        for i in range(1, n - 1):
            if board[i][0] == 'O': dfs(i, 0)
            if board[i][m - 1] == 'O': dfs(i, m - 1)
            
        # 第二阶段：秋后算账，扫荡全图
        for i in range(n):
            for j in range(m):
                if board[i][j] == 'O':
                    # 没有免死金牌的 'O'，直接被同化为 'X'
                    board[i][j] = 'X'
                elif board[i][j] == 'F':
                    # 有免死金牌的 'F'，恢复为原来的 'O'
                    board[i][j] = 'O'