import sys

# 放开递归深度限制，防止大网格长蛇阵爆栈
sys.setrecursionlimit(250000)

class Solution:
    def largestIsland(self, grid: list[list[int]]) -> int:
        n = len(grid)
        
        # 记录每个岛屿 ID 对应的面积
        # 巧妙放入 0:0，代表海洋或越界的面积为 0
        sizes = {0: 0}
        island_id = 2
        ans = 0
        
        # 内嵌 DFS，边染色边计算面积
        def dfs(i: int, j: int, current_id: int) -> int:
            if i < 0 or i == n or j < 0 or j == n or grid[i][j] != 1:
                return 0
            
            # 将陆地染色为专属 ID
            grid[i][j] = current_id
            
            # 自身的面积 1，加上四周蔓延的面积
            return 1 + dfs(i - 1, j, current_id) \
                     + dfs(i + 1, j, current_id) \
                     + dfs(i, j - 1, current_id) \
                     + dfs(i, j + 1, current_id)

        # 第一步：遍历网格，给所有岛屿登记造册
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    size = dfs(i, j, island_id)
                    sizes[island_id] = size
                    ans = max(ans, size)  # 记录不填海时的最大岛屿面积
                    island_id += 1 
                    
        # 第二步：遍历所有海洋，尝试填海造陆
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 0:
                    # 使用 set 天然去重四周相连的岛屿 ID
                    neighbor_ids = set()
                    if i > 0: neighbor_ids.add(grid[i - 1][j])
                    if i < n - 1: neighbor_ids.add(grid[i + 1][j])
                    if j > 0: neighbor_ids.add(grid[i][j - 1])
                    if j < n - 1: neighbor_ids.add(grid[i][j + 1])
                    
                    # 计算合并后的总面积 (自己填海的 1 + 四周不同岛屿的面积)
                    merge_size = 1 + sum(sizes[nid] for nid in neighbor_ids)
                    ans = max(ans, merge_size)
                    
        return ans