class Solution:
    def maxDistance(self, grid: list[list[int]]) -> int:
        n = len(grid)
        m = len(grid[0])
        
        # 严格保留静态数组队列的思路
        # 网格最多 n * m 个节点，一次分配到底，杜绝动态扩容
        max_q = n * m
        queue = [(0, 0)] * max_q
        
        l = 0
        r = 0
        seas = 0
        
        # 1. 遍历网格，初始化队列
        for i in range(n):
            for j in range(m):
                if grid[i][j] == 1:
                    queue[r] = (i, j)
                    r += 1
                else:
                    seas += 1
                    
        # 特判：没有海洋，或全是海洋
        if seas == 0 or seas == n * m:
            return -1
            
        # 方向数组 (为了更符合 Python 习惯写成了元组，底层逻辑与原版 move 完全一致)
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        level = 0
        
        # 2. 严格按 l 和 r 控制队列，按 size 控制层数
        while l < r:
            level += 1
            size = r - l  # 当前层的节点数量
            
            for _ in range(size):
                # 弹出队头
                x, y = queue[l]
                l += 1
                
                # 向四个方向蔓延
                for dx, dy in directions:
                    nx = x + dx
                    ny = y + dy
                    
                    if 0 <= nx < n and 0 <= ny < m and grid[nx][ny] == 0:
                        grid[nx][ny] = 2  # 原地标记为已访问，省去 visited 二维数组
                        # 加入队尾
                        queue[r] = (nx, ny)
                        r += 1
                        
        return level - 1