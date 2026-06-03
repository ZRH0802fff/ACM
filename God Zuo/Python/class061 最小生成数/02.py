import sys
import heapq

def solve():
    # 1. 快读：一次性读取所有标准输入进内存
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    idx = 0
    out = []
    
    while idx < len(input_data):
        n = int(input_data[idx])
        m = int(input_data[idx+1])
        idx += 2
        
        # 2. 构建邻接表 (动态空间)
        graph = [[] for _ in range(n + 1)] 
        for _ in range(m):
            u = int(input_data[idx])
            v = int(input_data[idx+1])
            w = int(input_data[idx+2])
            # 注意这里：把权重 w 放在前面，方便 heapq 自动按权重升序排序
            graph[u].append((w, v))
            graph[v].append((w, u))
            idx += 3
            
        # 3. 初始化 Prim 算法状态
        # 记录节点是否已被纳入最小生成树
        visited = [False] * (n + 1)
        visited[1] = True
        node_cnt = 1
        ans = 0
        
        # 初始化最小堆：将起点 1 的所有边入堆
        heap = []
        for edge in graph[1]:
            heapq.heappush(heap, edge)
            
        # 4. 开始像“摊大饼”一样向外扩张
        while heap:
            # 弹出当前能够触达的、最便宜的一条边
            cost, next_node = heapq.heappop(heap)
            
            # 如果这个节点还没被点亮过
            if not visited[next_node]:
                visited[next_node] = True
                node_cnt += 1
                ans += cost
                
                # 极致优化：如果所有节点都连通了，剩下的边就不用看了，直接下班！
                if node_cnt == n:
                    break
                    
                # 将新解锁的节点周围、且通向未知领域的边加入堆中
                for next_cost, neighbor in graph[next_node]:
                    if not visited[neighbor]: # 入堆前剪枝，控制堆的大小
                        heapq.heappush(heap, (next_cost, neighbor))
                        
        # 5. 结算判定
        if node_cnt == n:
            out.append(str(ans))
        else:
            out.append("orz")
            
    # 快写：批量输出
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()