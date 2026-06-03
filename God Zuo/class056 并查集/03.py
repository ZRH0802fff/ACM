class Solution:
    def minSwapsCouples(self, row: list[int]) -> int:
        n = len(row)
        couples = n // 2  # 一共有多少对情侣
        
        # 1. 初始化并查集
        father = list(range(couples))
        sets = couples  # 初始连通分量数量（假设大家都不挨着，各自独立）
        
        # 2. 递归找代表节点（自带路径压缩）
        def find(i: int) -> int:
            if i != father[i]:
                father[i] = find(father[i])
            return father[i]
            
        # 3. 合并操作
        def union(x: int, y: int):
            nonlocal sets  # 声明修改外部嵌套作用域中的 sets 变量
            fx = find(x)
            fy = find(y)
            if fx != fy:
                father[fx] = fy
                sets -= 1  # 每次成功连通两个不同的集合，连通分量减 1
                
        # 4. 遍历相邻的座位，建图
        for i in range(0, n, 2):
            # row[i] // 2 就是这个人的情侣 ID
            # 如果两个不同情侣家的人坐在一起了，就把这两个情侣 ID 连通起来
            union(row[i] // 2, row[i + 1] // 2)
            
        # 5. 核心公式：最少交换次数 = 总情侣对数 - 连通分量的数量
        return couples - sets