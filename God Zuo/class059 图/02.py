class Solution:
    def findOrder(self, numCourses: int, prerequisites: list[list[int]]) -> list[int]:
        # 邻接表建图（动态方式）
        # Pythonic: 使用列表推导式快速初始化 numCourses 个空列表
        graph = [[] for _ in range(numCourses)]
        
        # 入度表
        indegree = [0] * numCourses
        
        # 遍历依赖关系建图
        for a, b in prerequisites:
            # b 是 a 的前置课程，因此有向边为 b -> a
            graph[b].append(a)
            indegree[a] += 1
            
        # 数组模拟队列（预分配空间，在竞赛中这种写法极快）
        queue = [0] * numCourses
        l = r = 0
        
        # 将所有初始入度为 0 的节点（即没有前置依赖的课程）入队
        for i in range(numCourses):
            if indegree[i] == 0:
                queue[r] = i
                r += 1
                
        cnt = 0
        # 开始 BFS 拓扑排序
        while l < r:
            cur = queue[l]
            l += 1
            cnt += 1
            
            # 遍历当前课程解锁的所有后续课程
            for nxt in graph[cur]:
                indegree[nxt] -= 1
                # 如果后续课程的入度减为 0，说明其前置课程已全部学完，可以入队
                if indegree[nxt] == 0:
                    queue[r] = nxt
                    r += 1
                    
        # 如果处理的节点数等于总课程数，说明不存在环，直接返回 queue
        # （因为此时 queue 中刚好按顺序装满了所有课程）
        # 否则说明有环，无法完成所有课程，返回空列表
        return queue if cnt == numCourses else []