class Solution:
    def removeStones(self, stones: list[list[int]]) -> int:
        n = len(stones)
        
        # 1. 初始化并查集
        father = list(range(n))
        sets = n  # 初始假定每块石头都是一个独立的连通块
        
        # 2. 查找代表节点 (带路径压缩)
        def find(i: int) -> int:
            if i != father[i]:
                father[i] = find(father[i])
            return father[i]
            
        # 3. 合并操作
        def union(x: int, y: int):
            nonlocal sets
            fx = find(x)
            fy = find(y)
            if fx != fy:
                father[fx] = fy
                sets -= 1  # 每次成功连通两块石头，独立连通块数量减 1
                
        # 记录某行/某列第一次遇到的石头编号 (索引)
        row_first = {}
        col_first = {}
        
        # 4. 遍历所有石头，进行行和列的连通
        for i in range(n):
            row, col = stones[i]
            
            # 如果这行是第一次出现，记录下这块石头的编号
            if row not in row_first:
                row_first[row] = i
            else:
                # 否则，将当前石头与这行第一次出现的石头连通
                union(i, row_first[row])
                
            # 列的处理逻辑完全相同
            if col not in col_first:
                col_first[col] = i
            else:
                union(i, col_first[col])
                
        # 5. 核心公式：最多能移除的石头数 = 总石头数 - 连通块(大岛屿)的数量
        return n - sets