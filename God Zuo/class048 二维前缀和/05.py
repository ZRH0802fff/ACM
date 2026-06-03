from typing import List

class Solution:
    def fieldOfGreatestBlessing(self, fields: List[List[int]]) -> int:
        # 使用集合自动去重，收集所有出现过的边界坐标
        xs_set = set()
        ys_set = set()
        
        for x, y, r in fields:
            # 乘以 2 (左移 1 位) 避免计算 side / 2 时产生浮点数
            xs_set.add((x << 1) - r)
            xs_set.add((x << 1) + r)
            ys_set.add((y << 1) - r) 
            ys_set.add((y << 1) + r)
            
        # 坐标离散化：排序并建立 "真实坐标 -> 1-based 索引" 的映射字典
        x_to_idx = {val: i for i, val in enumerate(sorted(xs_set), 1)}
        y_to_idx = {val: i for i, val in enumerate(sorted(ys_set), 1)}
        
        sizex = len(x_to_idx)
        sizey = len(y_to_idx)
        
        # 构建二维差分数组，大小加 2 防止打标越界
        diff = [[0] * (sizey + 2) for _ in range(sizex + 2)]
        
        # 在差分数组中打标
        for x, y, r in fields:
            a = x_to_idx[(x << 1) - r]
            b = y_to_idx[(y << 1) - r]
            c = x_to_idx[(x << 1) + r]
            d = y_to_idx[(y << 1) + r]
            
            diff[a][b] += 1
            diff[c + 1][d + 1] += 1
            diff[c + 1][b] -= 1
            diff[a][d + 1] -= 1
            
        ans = 0
        
        # 利用前缀和还原原始矩阵，并同时计算最大力场强度
        for i in range(1, sizex + 1):
            for j in range(1, sizey + 1):
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1]
                if diff[i][j] > ans:
                    ans = diff[i][j]
                    
        return ans