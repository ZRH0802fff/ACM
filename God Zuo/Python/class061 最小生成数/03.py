class Solution:
    def minCostToSupplyWater(self, n: int, wells: list[int], pipes: list[list[int]]) -> int:
        edges = []
        
        # 1. 核心妙手：建立虚拟节点 0 (超级源点/地下水库)
        # 将所有“打井”操作，转化为从节点 0 连向对应房子的“边”
        for i in range(n):
            # wells[i] 对应的是房子 i + 1
            edges.append((0, i + 1, wells[i]))
            
        # 2. 把原有的管道（边）也加进来
        for u, v, w in pipes:
            edges.append((u, v, w))
            
        # 3. Kruskal 算法第一步：所有边按成本从小到大排序
        edges.sort(key=lambda x: x[2])
        
        # 4. 初始化并查集 (共 n + 1 个节点：0 到 n)
        father = list(range(n + 1))
        
        # 极速版 find (路径减半)
        def find(i: int) -> int:
            while i != father[i]:
                father[i] = father[father[i]]
                i = father[i]
            return i
            
        ans = 0
        edges_added = 0
        
        # 5. 贪心选边，构建最小生成树
        for u, v, w in edges:
            fx = find(u)
            fy = find(v)
            
            # 如果不在同一个集合，说明连通后不会成环，可以修这条管道/井
            if fx != fy:
                father[fx] = fy
                ans += w
                edges_added += 1
                
                # 极致剪枝：n + 1 个节点的图，最小生成树只需要恰好 n 条边
                if edges_added == n:
                    break
                    
        return ans