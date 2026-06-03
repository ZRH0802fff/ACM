from collections import deque
from typing import List

class Solution:
    def minimumTime(self, n: int, relations: List[List[int]], time: List[int]) -> int:
        # 1. 初始化邻接表和入度表
        # 课程编号从 1 到 n，所以数组大小开 n + 1
        graph = [[] for _ in range(n + 1)]
        indegree = [0] * (n + 1)
        
        # 2. 建图并统计入度
        for u, v in relations:
            graph[u].append(v)
            indegree[v] += 1
            
        # 3. 初始化拓扑排序队列
        # 将所有不需要先修课（入度为0）的课程加入队列
        queue = deque([i for i in range(1, n + 1) if indegree[i] == 0])
        
        # cost[i] 记录完成课程 i 所需要的最少总月份数
        cost = [0] * (n + 1)
        ans = 0
        
        # 4. 拓扑排序 + 动态规划求关键路径
        while queue:
            cur = queue.popleft()
            
            # 当前课程的完成时间 = 之前的最大依赖时间 + 自身花费的时间
            # 注意 time 数组是 0-indexed 的，所以是 time[cur - 1]
            cost[cur] += time[cur - 1]
            ans = max(ans, cost[cur])
            
            for nxt in graph[cur]:
                # 更新后续课程的最早可能开始时间（即所有先修课中最晚完成的那个时间）
                cost[nxt] = max(cost[nxt], cost[cur])
                indegree[nxt] -= 1
                if indegree[nxt] == 0:
                    queue.append(nxt)
                    
        return ans