import sys

# 放开递归深度限制，防止深层砖块长链爆栈
sys.setrecursionlimit(250000)

class Solution:
    def hitBricks(self, grid: list[list[int]], hits: list[list[int]]) -> list[int]:
        n, m = len(grid), len(grid[0])
        ans = [0] * len(hits)
        
        # 特判：如果只有 1 行，打碎砖块不可能导致下面的砖块掉落（因为没有下面）
        if n == 1:
            return ans
            
        # 1. 毁灭时刻：遍历所有 hits，将对应位置的砖块“打碎”
        # 如果原来是 1 (有砖)，打碎后变 0
        # 如果原来是 0 (没砖)，打空了变 -1
        for r, c in hits:
            grid[r][c] -= 1
            
        # 内嵌 DFS 函数：从 (i, j) 触发，寻找相连的 1 感染成 2
        # 返回新增的稳固砖块(2)的数量
        def dfs(i: int, j: int) -> int:
            if i < 0 or i == n or j < 0 or j == m or grid[i][j] != 1:
                return 0
                
            grid[i][j] = 2 # 标记为稳固
            # 洪水填充，返回包括自己在内的稳固数量
            return 1 + dfs(i + 1, j) \
                     + dfs(i - 1, j) \
                     + dfs(i, j + 1) \
                     + dfs(i, j - 1)
                     
        # 判断一个位置复原后，是否能“稳固”并值得触发 DFS 蔓延
        def worth(i: int, j: int) -> bool:
            return grid[i][j] == 1 and (
                i == 0 or  # 接在顶部，绝对稳固
                (i > 0 and grid[i - 1][j] == 2) or # 贴着上面稳固的砖
                (i < n - 1 and grid[i + 1][j] == 2) or # 贴着下面稳固的砖
                (j > 0 and grid[i][j - 1] == 2) or # 贴着左边稳固的砖
                (j < m - 1 and grid[i][j + 1] == 2) # 贴着右边稳固的砖
            )

        # 2. 冻结残局：在所有炮弹打完后，从顶部开始寻找幸存的稳固砖块，标记为 2
        for j in range(m):
            dfs(0, j)
            
        # 3. 时光倒流：从最后一次打击开始，逆向恢复砖块
        for i in range(len(hits) - 1, -1, -1):
            r, c = hits[i]
            # 恢复砖块状态：0 变回 1，-1 变回 0
            grid[r][c] += 1
            
            # 如果恢复出了一块砖(1)，并且它能与顶部或其它稳固砖块相连
            if worth(r, c):
                # dfs 返回这次一共救活了多少块砖
                # 减去 1 (它自己)，就是正向打碎时会掉落的悬空砖块数
                ans[i] = dfs(r, c) - 1
                
        return ans