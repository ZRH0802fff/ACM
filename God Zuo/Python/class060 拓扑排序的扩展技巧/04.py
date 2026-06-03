from collections import deque
from typing import List

class Solution:
    def maximumInvitations(self, favorite: List[int]) -> int:
        n = len(favorite)
        indegree = [0] * n
        
        # 1. 统计所有节点的入度
        for f in favorite:
            indegree[f] += 1
            
        # 2. 拓扑排序初始化：将所有入度为 0 的节点（即树枝的端点）入队
        queue = deque([i for i in range(n) if indegree[i] == 0])
        
        # deep[i] 表示不包括 i 在内，一直延伸到 i 之前的最长链的长度
        deep = [0] * n
        
        # 3. 拓扑排序（剪去树枝，并求出进入环的最大深度）
        while queue:
            cur = queue.popleft()
            nxt = favorite[cur]
            
            # 更新指向节点的深度
            deep[nxt] = max(deep[nxt], deep[cur] + 1)
            
            indegree[nxt] -= 1
            if indegree[nxt] == 0:
                queue.append(nxt)
                
        # 目前图中依然满足 indegree[i] > 0 的点，全都在环上！
        
        sum_of_small_rings = 0  # 可能性1：所有小环（大小为2）以及它们附带的链，总计节点数
        max_big_ring = 0        # 可能性2：最大环（大小 > 2）的节点数
        
        # 4. 遍历寻找所有的环
        for i in range(n):
            if indegree[i] > 0:
                # 发现一个新的环
                ring_size = 1
                indegree[i] = 0  # 标记为已访问，相当于从图中删除
                
                # 顺藤摸瓜遍历整个环
                nxt = favorite[i]
                while nxt != i:
                    ring_size += 1
                    indegree[nxt] = 0  # 标记为已访问
                    nxt = favorite[nxt]
                    
                # 分类讨论环的性质
                if ring_size == 2:
                    # 如果是两人互为最喜欢，可以把他们分别带的最长链（树枝）加上
                    # 并且不同的 2-环 桌子可以拼在一起，所以累加
                    sum_of_small_rings += 2 + deep[i] + deep[favorite[i]]
                else:
                    # 如果是 >2 的大环，只能单独坐一桌，且无法附带任何树枝，取最大值
                    max_big_ring = max(max_big_ring, ring_size)
                    
        # 返回两种情况的最大值
        return max(sum_of_small_rings, max_big_ring)