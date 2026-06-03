from typing import List

class Solution:
    def largest1BorderedSquare(self, grid: List[List[int]]) -> int:
        n = len(grid)
        m = len(grid[0])

        # 内部辅助函数：获取网格值，越界返回0
        # 注意：Python支持负数索引(从后往前)，因此必须显式拦截 i < 0 和 j < 0
        def get_val(i: int, j: int) -> int:
            return 0 if i < 0 or j < 0 else grid[i][j]

        # 1. 原地构建二维前缀和，完美保持 O(1) 额外空间复杂度
        for i in range(n):
            for j in range(m):
                grid[i][j] += get_val(i, j - 1) + get_val(i - 1, j) - get_val(i - 1, j - 1)

        # 内部辅助函数：查询 (a, b) 到 (c, d) 区域的累加和
        def region_sum(a: int, b: int, c: int, d: int) -> int:
            if a > c or b > d:
                return 0
            return grid[c][d] - get_val(c, b - 1) - get_val(a - 1, d) + get_val(a - 1, b - 1)

        # 提前剪枝：如果整个矩阵的累加和为0，说明根本没有1，直接返回0
        if region_sum(0, 0, n - 1, m - 1) == 0:
            return 0

        # 记录最大正方形的边长（上面已经排除了全0，所以至少有1个1，起步边长为1）
        ans = 1

        # 遍历所有的左上角点 (a, b)
        for a in range(n):
            for b in range(m):
                # c, d 为右下角点，k 为当前尝试的边长
                # 核心优化：直接从比当前最大边长 ans 大 1 的尺寸开始尝试探测
                c, d, k = a + ans, b + ans, ans + 1
                
                while c < n and d < m:
                    # 边界全为 1 的条件：外层正方形总和 - 内层正方形总和 == 周长
                    # 正方形周长的格子数为 4 * (k - 1)，使用位运算 << 2 加速
                    outer = region_sum(a, b, c, d)
                    inner = region_sum(a + 1, b + 1, c - 1, d - 1)
                    
                    if outer - inner == (k - 1) << 2:
                        ans = k
                    
                    # 扩大尝试的边长
                    c += 1
                    d += 1
                    k += 1

        return ans * ans