# 测试链接 : https://leetcode.cn/problems/loud-and-rich/
from collections import deque
from typing import List

class Solution:
    def loudAndRich(self, richer: List[List[int]], quiet: List[int]) -> List[int]:
        n=len(quiet)
        graph=[[] for _ in range(n)]
        indegree=[0]*n
        for u,v in richer:
            graph[u].append(v)
            indegree[v]+=1
        queue=deque([i for i in range(n) if indegree[i]==0])
        ans=[i for i in range(n)]
        while queue:
            cur=queue.popleft()
            for nxt in graph[cur]:
                if quiet[ans[nxt]]>quiet[ans[cur]]:
                    ans[nxt]=ans[cur]
                indegree[nxt]-=1
                if indegree[nxt]==0:
                    queue.append(nxt)
        return ans  