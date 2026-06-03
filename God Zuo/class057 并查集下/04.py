class Solution:
    def minMalwareSpread(self, graph: list[list[int]], initial: list[int]) -> int:
        n = len(graph)
        
        # 使用哈希集合存储病毒，提供 O(1) 的极速查询
        virus_set = set(initial)
        
        # 1. 初始化并查集（注意：只用于普通节点）
        father = list(range(n))
        size = [1] * n
        
        # 极速版查找代表节点 (路径减半)
        def find(i: int) -> int:
            while i != father[i]:
                father[i] = father[father[i]]
                i = father[i]
            return i
            
        def union(x: int, y: int):
            fx = find(x)
            fy = find(y)
            if fx != fy:
                father[fx] = fy
                size[fy] += size[fx]
                
        # 2. 隔离病毒，只让普通节点互相连通合并成“岛屿”
        for i in range(n):
            if i in virus_set:
                continue
            # 因为无向图的邻接矩阵是对称的，所以从 i + 1 开始遍历即可，节省一半时间
            for j in range(i + 1, n):
                if j not in virus_set and graph[i][j] == 1:
                    union(i, j)
                    
        # infect 数组：记录普通节点岛屿的“感染源”状态
        # -1: 绝对安全（没有病毒相连）
        # >=0: 只有唯一的感染源（记录病毒的索引）
        # -2: 被多个病毒包围，没救了！
        infect = [-1] * n
        
        # 3. 让病毒去“触碰”普通节点岛屿，更新感染源状态
        for sick in initial:
            for neighbor in range(n):
                # 如果这个邻居是普通节点，且与病毒相连
                if neighbor not in virus_set and graph[sick][neighbor] == 1:
                    fn = find(neighbor)
                    
                    if infect[fn] == -1:
                        # 第一次被病毒发现
                        infect[fn] = sick
                    elif infect[fn] != -2 and infect[fn] != sick:
                        # 被另一个不同的病毒发现了，彻底没救了
                        infect[fn] = -2
                        
        # cnts[i] 表示如果删掉病毒 i，能挽救多少个普通节点
        cnts = [0] * n
        
        # 4. 统计拯救数据
        for i in range(n):
            # 只有当 i 是某个平民岛屿的代表节点，且恰好只有唯一感染源时，才计算战果
            if i == father[i] and infect[i] >= 0:
                cnts[infect[i]] += size[i]
                
        # 5. 找出能拯救最多人的病毒，如果有并列，取索引最小的
        initial.sort()
        ans = initial[0]
        max_saved = cnts[ans]
        
        for i in initial:
            if cnts[i] > max_saved:
                ans = i
                max_saved = cnts[i]
                
        return ans