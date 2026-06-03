# 测试链接 : https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/
from collections import deque
from typing import List

class Solution:
    def maximumInvitations(self, favorite: List[int]) -> int:
        n=len(favorite)
        indegree=[0]*n
        for v in favorite:
            indegree[v]+=1
        deep=[0]*n
        queue=deque([i for i in range(n) if indegree[i]==0])
        while queue:
            cur=queue.popleft()
            nxt=favorite[cur]
            deep[nxt] = max(deep[nxt], deep[cur] + 1)
            indegree[nxt]-=1
            if indegree[nxt]==0:
                queue.append(nxt)
        
        sm1=0
        sm2=0
        for i in range(n):
            if indegree[i]!=0:
                ring=1
                j=favorite[i]
                indegree[i]=0
                while j !=i:
                    indegree[j]=0
                    j=favorite[j]
                    ring+=1
                if ring==2:
                    sm1+=deep[i]+deep[favorite[i]]+2
                else:
                    sm2=max(sm2,ring)
        return max(sm1,sm2)