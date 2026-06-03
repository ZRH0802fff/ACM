# 测试链接 : https://leetcode.cn/problems/course-schedule-ii/
class Solution:
    def findOrder(self, numCourses , prerequisites ):
        graph=[[] for _ in range(numCourses)]
        indegree=[0]*numCourses
        for a,b in prerequisites:
            graph[b].append(a)
            indegree[a]+=1
        queue=[0]*numCourses
        l=r=0
        for i in range(numCourses):
            if indegree[i]==0:
                queue[r]=i
                r+=1
        cnt=0
        while l<r:
            cur=queue[l]
            l+=1
            cnt+=1
            for nxt in graph[cur]:
                indegree[nxt]-=1
                if indegree[nxt]==0:
                    queue[r]=nxt
                    r+=1
        return queue if cnt==numCourses else []