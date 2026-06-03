import sys
from collections import deque

def main():
    # 竞赛向快读：一次性读取所有输入，这在Python中是最快的I/O方式
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    MOD = 80112002
    
    while True:
        try:
            n_str = next(iterator)
        except StopIteration:
            break
            
        n = int(n_str)
        m = int(next(iterator))
        
        # 1. 链式前向星数组预分配内存
        # head[u] 存储节点 u 的第一条边的索引
        head = [0] * (n + 1)
        # next_edge[i] 存储第 i 条边的下一条同源边的索引
        next_edge = [0] * (m + 1)
        # to[i] 存储第 i 条边指向的节点
        to = [0] * (m + 1)
        cnt = 1  # 边计数器，从 1 开始
        
        # 拓扑排序所需状态数组
        in_degree = [0] * (n + 1)
        lines = [0] * (n + 1)
        
        # 2. 建图 (将 addEdge 逻辑内联展开，省去 Python 函数调用的开销)
        for _ in range(m):
            u = int(next(iterator))
            v = int(next(iterator))
            
            # addEdge 核心逻辑
            next_edge[cnt] = head[u]
            to[cnt] = v
            head[u] = cnt
            cnt += 1
            
            # 统计入度
            in_degree[v] += 1
            
        # 3. 拓扑排序初始化
        queue = deque()
        for i in range(1, n + 1):
            if in_degree[i] == 0:
                queue.append(i)
                lines[i] = 1
                
        ans = 0
        
        # 4. 拓扑排序执行
        while queue:
            u = queue.popleft()
            
            # 通过 head[u] == 0 即可判断是否有出边，省去了额外维护出度数组
            if head[u] == 0:
                ans = (ans + lines[u]) % MOD
            else:
                # 遍历链式前向星
                ei = head[u]
                while ei != 0:
                    v = to[ei]
                    lines[v] = (lines[v] + lines[u]) % MOD
                    in_degree[v] -= 1
                    if in_degree[v] == 0:
                        queue.append(v)
                    # 移动到下一条边
                    ei = next_edge[ei]
                    
        print(ans)

if __name__ == '__main__':
    main()