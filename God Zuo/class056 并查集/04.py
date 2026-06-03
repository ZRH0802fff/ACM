class Solution:
    def numSimilarGroups(self, strs: list[str]) -> int:
        n = len(strs)
        m = len(strs[0])
        
        # 1. 初始化并查集
        father = list(range(n))
        sets = n  # 初始假定所有字符串自成一派
        
        # 2. 查找代表节点 (带路径压缩)
        # 题目数据限制 N <= 300，递归深度绝对安全，不会爆栈
        def find(i: int) -> int:
            if i != father[i]:
                father[i] = find(father[i])
            return father[i]
            
        # 3. 合并操作
        def union(x: int, y: int):
            nonlocal sets  # 声明修改外部的 sets 变量
            fx = find(x)
            fy = find(y)
            if fx != fy:
                father[fx] = fy
                sets -= 1
                
        # 4. 暴力枚举所有字符串对 (i, j)
        for i in range(n):
            for j in range(i + 1, n):
                # 极其重要的常数优化：
                # 只有当它们目前不在同一个集合时，才去执行耗时的字符串相似度比对
                if find(i) != find(j):
                    diff = 0
                    s1 = strs[i]
                    s2 = strs[j]
                    
                    # 检查相似度：逐字符比对
                    for k in range(m):
                        if s1[k] != s2[k]:
                            diff += 1
                            # 提前剪枝：只要差异数超过 2，绝对不可能相似，立刻中止比对
                            if diff > 2:
                                break
                                
                    # 差异为 0（本身相同）或为 2（只交换了一次）即为相似
                    if diff == 0 or diff == 2:
                        union(i, j)
                        
        return sets