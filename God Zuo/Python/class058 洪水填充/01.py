import sys

# 极其重要：对于二维网格的 DFS，最坏情况下递归深度会达到 n * m
# LeetCode 岛屿最大是 300 * 300 = 90000，所以设为 100000 以上防爆栈
sys.setrecursionlimit(150000)

class Solution:
    def numIslands(self, grid: list[list[str]]) -> int:
        if not grid or not grid[0]:
            return 0
            
        n = len(grid)
        m = len(grid[0])
        islands = 0
        
        # 内嵌 DFS 函数，可以直接读取外层的 n, m 和 grid
        def dfs(i: int, j: int):
            # 边界越界，或者是水('0')，直接返回
            if i < 0 or i == n or j < 0 or j == m or grid[i][j] != '1':
                return
                
            # 核心：沉岛策略！
            # 只要遍历过，就把陆地改成水，防止死循环重复遍历
            grid[i][j] = '0'
            
            # 像四周的陆地继续蔓延 (洪水填充)
            dfs(i - 1, j) # 上
            dfs(i + 1, j) # 下
            dfs(i, j - 1) # 左
            dfs(i, j + 1) # 右

        # 遍历整个棋盘寻找未发现的岛屿
        for i in range(n):
            for j in range(m):
                # 只要发现了一块陆地，就说明发现了一个新岛屿
                if grid[i][j] == '1':
                    islands += 1
                    # 派出空降兵，把和这块陆地相连的所有陆地全部“炸沉”（变成 '0'）
                    dfs(i, j)
                    
        return islands