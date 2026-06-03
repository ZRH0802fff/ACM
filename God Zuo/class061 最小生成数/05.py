import sys

def solve():
    # 1. 极致快读：一次性将所有输入读取到内存并分割
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    idx = 0
    out = []
    
    # 兼容多组测试数据
    while idx < len(input_data):
        n = int(input_data[idx])
        m = int(input_data[idx+1])
        idx += 2
        
        edges = []
        for _ in range(m):
            u = int(input_data[idx])
            v = int(input_data[idx+1])
            w = int(input_data[idx+2])
            edges.append((u, v, w))
            idx += 3
            
        # 2. 核心：将所有边按权重从小到大排序
        edges.sort(key=lambda x: x[2])
        
        # 初始化并查集
        father = list(range(n + 1))
        
        # 极速版查找代表节点 (路径减半)
        def find(i: int) -> int:
            while i != father[i]:
                father[i] = father[father[i]]
                i = father[i]
            return i
            
        ans = 0
        edge_cnt = 0
        
        # 3. 贪心合并
        for u, v, w in edges:
            fx = find(u)
            fy = find(v)
            
            if fx != fy:
                father[fx] = fy
                edge_cnt += 1
                
                # 记录加入生成树的最大边权。
                # 因为 edges 是从小到大排好序的，其实直接 ans = w 也可以
                ans = max(ans, w)
                
                # 如果已经选出了 n - 1 条边，说明所有路口都已连通，直接提前下班
                if edge_cnt == n - 1:
                    break
                    
        # 按照题目要求，输出：改造的道路数(n-1) 以及 最大分值
        out.append(f"{n - 1} {ans}")
        
    # 快写输出
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()