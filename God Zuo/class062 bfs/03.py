from collections import deque

class Solution:
    def minimumObstacles(self, grid: list[list[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        # 初始化距离数组，全部设为无穷大
        distance = [[float('inf')] * n for _ in range(m)]
        distance[0][0] = 0
        
        # 使用 deque 实现 0-1 BFS
        # 存放元素的格式为元组 (x, y)
        q = deque([(0, 0)])
        
        # 方向数组：上、下、左、右
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        while q:
            # 从队头弹出一个节点
            x, y = q.popleft()
            
            # 找到终点直接返回（因为 0-1 BFS 保证首次弹出即为最短路径）
            if x == m - 1 and y == n - 1:
                return distance[x][y]
                
            # 向四个方向扩展
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                
                # 判断是否越界
                if 0 <= nx < m and 0 <= ny < n:
                    # 移动到相邻格子的代价（0 或 1）
                    cost = grid[nx][ny]
                    
                    # 如果能找到更短的距离，则更新并入队
                    if distance[x][y] + cost < distance[nx][ny]:
                        distance[nx][ny] = distance[x][y] + cost
                        
                        # 核心逻辑：
                        # 如果代价是 0，说明没遇到障碍，优先级极高，塞入队头！
                        # 如果代价是 1，说明遇到了障碍，优先级降低，塞入队尾！
                        if cost == 0:
                            q.appendleft((nx, ny))
                        else:
                            q.append((nx, ny))
                            
        return -1