class Solution:
    def numberOfGoodPaths(self, vals: list[int], edges: list[list[int]]) -> int:
        n = len(vals)
        
        # father 记录并查集的代表节点
        # 核心规定：代表节点一定是当前集合中 val 最大的那个节点！
        father = list(range(n))
        # maxcnt 记录当前集合中，最大值的个数
        maxcnt = [1] * n
        
        # 极速版查找代表节点 (路径减半，防爆栈且常数极小)
        def find(i: int) -> int:
            while i != father[i]:
                father[i] = father[father[i]]
                i = father[i]
            return i
            
        # 核心：按照边两端节点的最大值从小到大排序
        # 这样每次合并时，我们面对的一定是当前已知世界里的“最大值”
        edges.sort(key=lambda e: max(vals[e[0]], vals[e[1]]))
        
        # 初始时，每个单独的节点都是一条长度为 1 的好路径
        ans = n
        
        # 依次从小到大处理边
        for u, v in edges:
            fx = find(u)
            fy = find(v)
            
            if fx != fy:
                # 谁的值大，谁就当新集合的老大 (代表节点)
                if vals[fx] > vals[fy]:
                    father[fy] = fx
                elif vals[fx] < vals[fy]:
                    father[fx] = fy
                else:
                    # 如果两个集合的老大值一样大！
                    # 那么左边集合的每个最大值节点，都能和右边集合的每个最大值节点连通形成好路径
                    ans += maxcnt[fx] * maxcnt[fy]
                    # 选 fx 继续当老大，并且把 fy 集合里的最大值个数合并过来
                    father[fy] = fx
                    maxcnt[fx] += maxcnt[fy]
                    
        return ans

# ==========================================
# 课上讲解的例子测试 (可在本地直接运行)
# ==========================================
if __name__ == '__main__':
    sol = Solution()
    
    # 课上例子1
    vals1 = [2, 1, 1, 2, 2, 1, 1, 2]
    edges1 = [[0, 1], [0, 2], [1, 3], [2, 4], [2, 5], [5, 6], [6, 7]]
    print(f"例子1的答案: {sol.numberOfGoodPaths(vals1, edges1)}")  # 期望输出类似课上结果

    # 课上例子2
    vals2 = [1, 2, 2, 3, 1, 2, 2, 1, 1, 3, 3, 3, 3]
    edges2 = [
        [0, 1], [0, 2], [0, 3], [1, 4], [4, 7], [4, 8],
        [3, 5], [3, 6], [6, 9], [6, 10], [6, 11], [9, 12]
    ]
    print(f"例子2的答案: {sol.numberOfGoodPaths(vals2, edges2)}")