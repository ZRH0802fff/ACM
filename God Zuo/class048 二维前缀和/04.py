from typing import List

class Solution:
    def possibleToStamp(self, grid: List[List[int]], stampHeight: int, stampWidth: int) -> bool:
        n = len(grid)
        m = len(grid[0])
        
        # 1. 构建二维前缀和数组 (大小 n+1 x m+1，为了方便处理边界)
        # pre_sum[i][j] 记录原图中 (0,0) 到 (i-1,j-1) 区域内 1 的个数
        pre_sum = [[0] * (m + 1) for _ in range(n + 1)]
        for i in range(n):
            for j in range(m):
                pre_sum[i + 1][j + 1] = (pre_sum[i][j + 1] + pre_sum[i + 1][j] 
                                         - pre_sum[i][j] + grid[i][j])
        
        # 2. 构建二维差分数组 (大小 n+2 x m+2，为了防止打标时越界)
        diff = [[0] * (m + 2) for _ in range(n + 2)]
        
        # a, b 为邮票左上角在 1-based 索引中的坐标
        for a in range(1, n - stampHeight + 2):
            c = a + stampHeight - 1  # 邮票右下角的行号
            for b in range(1, m - stampWidth + 2):
                d = b + stampWidth - 1  # 邮票右下角的列号
                
                # 查询该区域是否有被占据的格子（也就是累加和是否为0）
                region_sum = pre_sum[c][d] - pre_sum[c][b - 1] - pre_sum[a - 1][d] + pre_sum[a - 1][b - 1]
                
                # 如果完全是0，说明可以贴邮票，在差分数组中进行 2D 更新
                if region_sum == 0:
                    diff[a][b] += 1
                    diff[c + 1][d + 1] += 1
                    diff[a][d + 1] -= 1
                    diff[c + 1][b] -= 1
                    
        # 3. 还原差分数组，检查所有空格子是否都被覆盖
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                # 差分数组自身求前缀和，还原出每个格子被邮票覆盖的次数
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1]
                
                # 原始矩阵里：grid[i-1][j-1] == 0 说明是个洞
                # 差分矩阵还原后：diff[i][j] == 0 说明洞上没有贴上邮票
                if grid[i - 1][j - 1] == 0 and diff[i][j] == 0:
                    return False
                    
        return True