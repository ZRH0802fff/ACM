class Solution:
    def findAllPeople(self, n: int, meetings: list[list[int]], firstPerson: int) -> list[int]:
        # 1. 按照会议时间从小到大排序
        meetings.sort(key=lambda x: x[2])
        
        # 初始化并查集与秘密标记
        father = list(range(n))
        secret = [False] * n
        
        # 初始状态：专家 0 和 firstPerson 知道秘密，将他们连通
        father[firstPerson] = 0
        secret[0] = True
        
        # 查找代表节点 (带路径压缩)
        def find(i: int) -> int:
            if i != father[i]:
                father[i] = find(father[i])
            return father[i]
            
        # 合并操作：顺便传递“秘密”属性
        def union(x: int, y: int):
            fx = find(x)
            fy = find(y)
            if fx != fy:
                father[fx] = fy
                # 只要两拨人里有一拨知道秘密，合并后的整个集合就全知道了
                secret[fy] |= secret[fx]

        m = len(meetings)
        l = 0
        while l < m:
            r = l
            # 圈出所有在【同一时刻】发生的会议 [l, r]
            while r + 1 < m and meetings[l][2] == meetings[r + 1][2]:
                r += 1
                
            # 第一阶段：先让当前时刻开会的所有人无脑连通
            for i in range(l, r + 1):
                union(meetings[i][0], meetings[i][1])
                
            # 第二阶段：清算！(动态撤销)
            # 秘密共享是瞬时的，如果这批人开完会后，他们的代表节点仍然不知道秘密，
            # 说明他们这帮人只是互相聊了会天，并没有接触到核心圈子。
            # 为了不影响未来的会议，必须把他们互相之间的连接“断开”，恢复单身状态。
            for i in range(l, r + 1):
                a, b, _ = meetings[i]
                if not secret[find(a)]:
                    father[a] = a
                    father[b] = b
                    
            l = r + 1
            
        # 收集所有知晓秘密的专家
        ans = []
        for i in range(n):
            if secret[find(i)]:
                ans.append(i)
                
        return ans