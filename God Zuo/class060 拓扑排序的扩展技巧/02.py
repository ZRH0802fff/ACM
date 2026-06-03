from collections import deque
from typing import List

class Solution:
    def loudAndRich(self, richer: List[List[int]], quiet: List[int]) -> List[int]:
        n = len(quiet)
        
        # 1. 初始化邻接表和入度表
        graph = [[] for _ in range(n)]
        indegree = [0] * n
        
        # 2. 建图与统计入度 (Pythonic解包写法)
        for u, v in richer:
            graph[u].append(v)
            indegree[v] += 1
            
        # 3. 初始化拓扑排序队列 (一步到位的列表推导式)
        queue = deque([i for i in range(n) if indegree[i] == 0])
        
        # 4. 初始化答案数组 ans[i] = i
        ans = list(range(n))
        
        # 5. 拓扑排序与动态规划状态转移
        while queue:
            cur = queue.popleft()
            
            for nxt in graph[cur]:
                # 如果 cur 拥有的最安静的人，比 nxt 拥有的最安静的人还要安静
                # 则更新 nxt 的答案
                if quiet[ans[cur]] < quiet[ans[nxt]]:
                    ans[nxt] = ans[cur]
                
                # 消除当前节点的依赖
                indegree[nxt] -= 1
                if indegree[nxt] == 0:
                    queue.append(nxt)
                    
        return ans