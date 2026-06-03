# 点的最大数量
MAXN = 11

# 边的最大数量
# 只有链式前向星方式建图需要这个数量
# 注意如果无向图的最大数量是m条边，数量要准备m*2
MAXM = 21

# 邻接矩阵方式建图
graph1 = [[0] * MAXN for _ in range(MAXN)]

# 邻接表方式建图
graph2 = []

# 链式前向星方式建图
head = [0] * MAXN
nxt = [0] * MAXM  # 用 nxt 代替 next，避免覆盖 Python 内置函数
to = [0] * MAXM
weight = [0] * MAXM
cnt = 1


def build(n):
    global cnt, graph2
    # 邻接矩阵清空
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            graph1[i][j] = 0
            
    # 邻接表清空和准备 
    # Pythonic 写法：直接用列表推导式生成 n+1 个空列表
    graph2 = [[] for _ in range(n + 1)]
    
    # 链式前向星清空
    cnt = 1
    # Python中可直接对需要的部分切片赋值，或简单循环初始化
    for i in range(1, n + 1):
        head[i] = 0


# 链式前向星加边
def add_edge(u, v, w):
    global cnt
    # u -> v , 边权重是w
    nxt[cnt] = head[u]
    to[cnt] = v
    weight[cnt] = w
    head[u] = cnt
    cnt += 1


# 三种方式建立有向带权图
def direct_graph(edges):
    for u, v, w in edges:  # Pythonic 写法：直接解包
        # 邻接矩阵建图
        graph1[u][v] = w
        # 邻接表建图 (使用元组代替数组，更轻量高效)
        graph2[u].append((v, w))
        # 链式前向星建图
        add_edge(u, v, w)


# 三种方式建立无向带权图
def undirect_graph(edges):
    for u, v, w in edges:
        # 邻接矩阵建图
        graph1[u][v] = w
        graph1[v][u] = w
        # 邻接表建图
        graph2[u].append((v, w))
        graph2[v].append((u, w))
        # 链式前向星建图
        add_edge(u, v, w)
        add_edge(v, u, w)


def traversal(n):
    print("邻接矩阵遍历 :")
    for i in range(1, n + 1):
        # Pythonic写法：切片并用 join 快速转字符串打印
        print(" ".join(map(str, graph1[i][1:n + 1])))
        
    print("邻接表遍历 :")
    for i in range(1, n + 1):
        print(f"{i}(邻居、边权) : ", end="")
        for v, w in graph2[i]:
            print(f"({v},{w}) ", end="")
        print()
        
    print("链式前向星 :")
    for i in range(1, n + 1):
        print(f"{i}(邻居、边权) : ", end="")
        # 链式前向星遍历方式
        ei = head[i]
        while ei > 0:
            print(f"({to[ei]},{weight[ei]}) ", end="")
            ei = nxt[ei]
        print()


if __name__ == "__main__":
    # 理解了带权图的建立过程，也就理解了不带权图
    # 点的编号为1...n
    # 例子1有向带权图
    n1 = 4
    edges1 = [[1, 3, 6], [4, 3, 4], [2, 4, 2], [1, 2, 7], [2, 3, 5], [3, 1, 1]]
    build(n1)
    direct_graph(edges1)
    traversal(n1)
    
    print("==============================")
    
    # 例子2无向带权图
    n2 = 5
    edges2 = [[3, 5, 4], [4, 1, 1], [3, 4, 2], [5, 2, 4], [2, 3, 7], [1, 5, 5], [4, 2, 6]]
    build(n2)
    undirect_graph(edges2)
    traversal(n2)