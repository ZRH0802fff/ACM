import heapq

class Solution:
    def trapRainWater(self, heightMap: list[list[int]]) -> int:
        # 特判：如果网格小于 3x3，连内部凹陷都形不成，根本接不到水
        if not heightMap or not heightMap[0] or len(heightMap) < 3 or len(heightMap[0]) < 3:
            return 0
            
        m, n = len(heightMap), len(heightMap[0])
        visited = [[False] * n for _ in range(m)]
        heap = []
        
        # 1. 筑起第一道外墙：将所有边界元素加入小根堆
        # 堆里的元素格式为：(水线 w, 行坐标 r, 列坐标 c)
        # Python 的 heapq 默认按元组的第一个元素（水线）进行升序排序
        for i in range(m):
            for j in range(n):
                if i == 0 or i == m - 1 or j == 0 or j == n - 1:
                    heapq.heappush(heap, (heightMap[i][j], i, j))
                    visited[i][j] = True
                    
        ans = 0
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        # 2. 从最矮的墙壁开始，像剥洋葱一样向内部进军
        while heap:
            w, r, c = heapq.heappop(heap)
            
            # 当前格子能接的水，就是它的水线减去它的真实物理高度
            # (对于外墙和比水线高的内部块，这里刚好是 0)
            ans += w - heightMap[r][c]
            
            # 遍历四个方向的邻居
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < m and 0 <= nc < n and not visited[nr][nc]:
                    visited[nr][nc] = True
                    # 核心逻辑：邻居被拉入新围墙！
                    # 它的新水线是：它本身的物理高度 与 传过来的水线 w 中的最大值
                    heapq.heappush(heap, (max(heightMap[nr][nc], w), nr, nc))
                    
        return ans