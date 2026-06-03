from typing import List


class NumMatrix:

    def __init__(self, matrix: List[List[int]]):
        if not matrix or not matrix[0]:
            # 空矩阵情况（LeetCode约束中不会出现，但保持健壮性）
            self.sum = [[0]]
            return
        n = len(matrix)
        m = len(matrix[0])
        # sum[i][j] 表示从 (0,0) 到 (i-1,j-1) 的二维前缀和
        self.sum = [[0] * (m + 1) for _ in range(n + 1)]
        # 先把原矩阵拷贝到 sum 的 1-based 区域
        for c in range(n):
            for d in range(m):
                self.sum[c + 1][d + 1] = matrix[c][d]
        # 构建二维前缀和
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                self.sum[i][j] += self.sum[i][j - 1] + self.sum[i - 1][j] - self.sum[i - 1][j - 1]

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        # 标准二维前缀和查询公式
        # sumRegion(row1, col1, row2, col2) = 前缀[row2+1][col2+1] - 前缀[row2+1][col1] - 前缀[row1][col2+1] + 前缀[row1][col1]
        return (self.sum[row2 + 1][col2 + 1]
                - self.sum[row2 + 1][col1]
                - self.sum[row1][col2 + 1]
                + self.sum[row1][col1])