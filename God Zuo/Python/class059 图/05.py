from collections import deque

class Solution:
    def movesToStamp(self, stamp: str, target: str) -> list[int]:
        m = len(stamp)
        n = len(target)
        
        # 入度表：记录每个起点 i 的窗口内，有多少个字符与 stamp 不匹配
        # 初始化时假设全部不匹配，入度均为 m
        indegree = [m] * (n - m + 1)
        
        # 邻接表：记录某个位置如果变成 '?' (褪色)，可以帮助哪些窗口减少入度
        graph = [[] for _ in range(n)]
        
        queue = deque()
        
        # 1. 初始化入度表和建图
        for i in range(n - m + 1):
            for j in range(m):
                if target[i + j] == stamp[j]:
                    indegree[i] -= 1
                    # 如果该窗口完全匹配印章，入度减为0，入队
                    if indegree[i] == 0:
                        queue.append(i)
                else:
                    # 如果不匹配，说明窗口 i 依赖位置 i + j 变成 '?'
                    graph[i + j].append(i)
                    
        # 同一个位置取消错误不要重复统计
        visited = [False] * n
        path = []
        
        # 2. 拓扑排序 (BFS)
        while queue:
            cur = queue.popleft()
            path.append(cur)
            
            # 遍历当前窗口覆盖的 m 个位置
            for i in range(m):
                idx = cur + i
                if not visited[idx]:
                    visited[idx] = True
                    # 这个位置现在褪色成了 '?'，通知所有依赖该位置的窗口
                    for nxt in graph[idx]:
                        indegree[nxt] -= 1
                        if indegree[nxt] == 0:
                            queue.append(nxt)
                            
        # 3. 检查是否所有的窗口都被成功处理
        if len(path) != n - m + 1:
            return []
            
        # 4. 因为我们是逆推（褪色操作），所以真正的盖章顺序需要逆序返回
        return path[::-1]