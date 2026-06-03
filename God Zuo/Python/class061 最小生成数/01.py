import sys

def solve():
    # 1. 快读：一次性读取所有标准输入，按空格或换行分割
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    out = []
    
    # 兼容可能存在的多组测试数据 (类似 Java 的 while(EOF))
    while idx < len(input_data):
        n = int(input_data[idx])
        m = int(input_data[idx+1])
        idx += 2
        
        # 读取 M 条边
        edges = []
        for _ in range(m):
            u = int(input_data[idx])
            v = int(input_data[idx+1])
            w = int(input_data[idx+2])
            edges.append((u, v, w))
            idx += 3
            
        # 2. 按照边的权重 w 从小到大排序
        edges.sort(key=lambda x: x[2])
        
        # 初始化并查集 (节点编号从 1 到 n)
        father = list(range(n + 1))
        
        # 3. 极速迭代版 find (路径减半压缩)
        def find(i):
            while i != father[i]:
                father[i] = father[father[i]]
                i = father[i]
            return i

        ans = 0
        edge_cnt = 0
        
        # 4. 贪心选取边
        for u, v, w in edges:
            fx = find(u)
            fy = find(v)
            
            # 如果 u 和 v 不在同一个集合，说明不会产生环，可以合并
            if fx != fy:
                father[fx] = fy
                ans += w
                edge_cnt += 1
                
                # 优化：一棵有 n 个节点的树刚好有 n-1 条边
                # 只要边数够了，剩下的边就不需要再看了
                if edge_cnt == n - 1:
                    break
                    
        # 5. 判断是否成功构建了最小生成树
        if edge_cnt == n - 1:
            out.append(str(ans))
        else:
            # 如果选出的边数不足 n-1，说明图是不连通的
            out.append("orz")
            
    # 快写：批量输出全部结果
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()