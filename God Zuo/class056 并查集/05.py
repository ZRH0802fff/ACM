class Solution:
    def numIslands(self, grid: list[list[str]]) -> int:
        if not grid or not grid[0]:
            return 0
            
        n = len(grid)
        m = len(grid[0])
        
        # 1. 初始化 father 数组 (一维展开)
        # 索引计算公式: index = i * m + j
        father = list(range(n * m))
        sets = 0
        
        # 2. 统计初始的陆地数量，并将其作为独立的连通分量
        for i in range(n):
            for j in range(m):
                if grid[i][j] == '1':
                    sets += 1
                    
        # 3. 极速版查找代表节点 (路径减半 Path Halving)
        # 既不会爆递归栈，也不需要额外开辟数组记录路径，常数极小
        def find(i: int) -> int:
            while i != father[i]:
                # 将当前节点直接挂到爷爷节点上，实现路径压缩
                father[i] = father[father[i]]
                i = father[i]
            return i
            
        # 4. 合并操作
        def union(r1: int, c1: int, r2: int, c2: int):
            nonlocal sets
            fx = find(r1 * m + c1)
            fy = find(r2 * m + c2)
            if fx != fy:
                father[fx] = fy
                sets -= 1  # 每次成功合并，岛屿数量减 1
                
        # 5. 遍历网格，执行合并
        for i in range(n):
            for j in range(m):
                if grid[i][j] == '1':
                    # 只需要查左边和上边，就能不重不漏地完成图的连通
                    if j > 0 and grid[i][j - 1] == '1':
                        union(i, j, i, j - 1)
                    if i > 0 and grid[i - 1][j] == '1':
                        union(i, j, i - 1, j)
                        
        return sets