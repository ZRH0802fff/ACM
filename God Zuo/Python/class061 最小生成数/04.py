class Solution:
    def distanceLimitedPathsExist(self, n: int, edges: list[list[int]], queries: list[list[int]]) -> list[bool]:
        # 1. 把边按长度从小到大排序
        edges.sort(key=lambda x: x[2])
        
        # 2. 离线查询技巧：给查询带上它原本的索引，然后按 limit 从小到大排序
        # 格式为: (起点, 终点, limit, 原始索引)
        questions = [(q[0], q[1], q[2], i) for i, q in enumerate(queries)]
        questions.sort(key=lambda x: x[2])
        
        # 初始化并查集
        father = list(range(n))
        
        # 极速版 find (路径减半压缩)
        def find(i: int) -> int:
            while i != father[i]:
                father[i] = father[father[i]]
                i = father[i]
            return i
            
        k = len(queries)
        m = len(edges)
        ans = [False] * k
        j = 0 # 记录当前加到了哪条边
        
        # 3. 按 limit 从小到大处理每个查询
        for p, q, limit, original_index in questions:
            
            # 双指针：只要边的长度严格小于当前查询的 limit，就统统加进并查集
            while j < m and edges[j][2] < limit:
                u, v = edges[j][0], edges[j][1]
                fu, fv = find(u), find(v)
                if fu != fv:
                    father[fu] = fv
                j += 1
                
            # 此时图中所有 < limit 的边都已经生效了，直接查两点是否连通
            ans[original_index] = (find(p) == find(q))
            
        return ans