from typing import List
from functools import cache

class Solution:

    # ==========================================
    # 方法一：暴力递归
    # ==========================================
    def minPathSum1(self, grid: List[List[int]]) -> int:
        # 利用内部函数，直接读取外部的 grid，不需要作为参数传来传去
        def dfs(i: int, j: int) -> int:
            if i == 0 and j == 0:
                return grid[0][0]
            
            up = float('inf')
            left = float('inf')
            
            if i - 1 >= 0:
                up = dfs(i - 1, j)
            if j - 1 >= 0:
                left = dfs(i, j - 1)
                
            return grid[i][j] + min(up, left)
            
        return dfs(len(grid) - 1, len(grid[0]) - 1)

    # ==========================================
    # 方法二：记忆化搜索 (严格对应原版逻辑的手动缓存)
    # ==========================================
    def minPathSum2(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        # Pythonic: 使用列表推导式初始化二维数组
        dp = [[-1] * m for _ in range(n)]

        def dfs(i: int, j: int) -> int:
            if dp[i][j] != -1:
                return dp[i][j]
            
            if i == 0 and j == 0:
                ans = grid[0][0]
            else:
                up = float('inf')
                left = float('inf')
                if i - 1 >= 0:
                    up = dfs(i - 1, j)
                if j - 1 >= 0:
                    left = dfs(i, j - 1)
                ans = grid[i][j] + min(up, left)
                
            dp[i][j] = ans
            return ans

        return dfs(n - 1, m - 1)

    # 💡 竞赛小贴士：在 Python 中，记忆化搜索最 Pythonic 的写法是直接加 @cache 装饰器
    # 这样连 dp 数组都不用手动声明，一行代码搞定缓存！
    # def minPathSum2_Pythonic(self, grid: List[List[int]]) -> int:
    #     @cache
    #     def dfs(i, j):
    #         if i == 0 and j == 0: return grid[0][0]
    #         up = dfs(i - 1, j) if i > 0 else float('inf')
    #         left = dfs(i, j - 1) if j > 0 else float('inf')
    #         return grid[i][j] + min(up, left)
    #     return dfs(len(grid) - 1, len(grid[0]) - 1)

    # ==========================================
    # 方法三：严格位置依赖的动态规划
    # ==========================================
    def minPathSum3(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        dp = [[0] * m for _ in range(n)]
        
        dp[0][0] = grid[0][0]
        
        # 初始化第一列
        for i in range(1, n):
            dp[i][0] = dp[i - 1][0] + grid[i][0]
            
        # 初始化第一行
        for j in range(1, m):
            dp[0][j] = dp[0][j - 1] + grid[0][j]
            
        # 普遍位置计算
        for i in range(1, n):
            for j in range(1, m):
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]
                
        return dp[n - 1][m - 1]

    # ==========================================
    # 方法四：严格位置依赖的动态规划 + 空间压缩技巧 (最优解)
    # ==========================================
    def minPathSum4(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        # 只需要一个长度为 m 的一维数组
        dp = [0] * m
        dp[0] = grid[0][0]
        
        # 先让 dp 表变成想象中二维表的第 0 行的数据
        for j in range(1, m):
            dp[j] = dp[j - 1] + grid[0][j]
            
        # 从第 1 行开始向下滚动更新
        for i in range(1, n):
            # 更新每一行的第 0 列元素
            dp[0] += grid[i][0]
            for j in range(1, m):
                # dp[j-1] 相当于左边的值，dp[j] 相当于上面的值
                dp[j] = min(dp[j - 1], dp[j]) + grid[i][j]
                
        return dp[m - 1]