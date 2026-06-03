# 测试链接 : https://leetcode.cn/problems/parallel-courses-iii/
from collections import deque
from typing import List

class Solution:
    def minimumTime(self, n: int, relations: List[List[int]], time: List[int]) -> int:
        graph=[[] for i in range(n+1)]
        indegree=[0]*(n+1)
        for u,v in relations:
            graph[u].append(v)
            indegree[v]+=1
        queue=deque([ i for i in range(1,n+1) if indegree[i]==0 ])
        cost=[0]*(n+1)
        ans=0
        while queue:
            cur=queue.popleft()
            cost[cur]+=time[cur-1]
            ans=max(ans,cost[cur])
            for nxt in graph[cur]:
                cost[nxt]=max(cost[nxt],cost[cur])
                indegree[nxt]-=1
                if indegree[nxt]==0:
                    queue.append(nxt)
        return ans