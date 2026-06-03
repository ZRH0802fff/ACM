# 测试链接 : https://www.luogu.com.cn/problem/U107394
import sys
import heapq

# 设定最大节点数和最大边数
MAXN = 100005
MAXM = 100005

# 建图相关，链式前向星
head = [0] * MAXN
next_edge = [0] * MAXM  # 避免使用 python 内置关键字 next
to = [0] * MAXM
cnt = 1

# 拓扑排序，入度表
indegree = [0] * MAXN

# 收集拓扑排序的结果
ans = [0] * MAXN


def build(n):
    """
    清理之前的脏数据，用于处理多组测试用例
    """
    global cnt
    cnt = 1
    # 只需要清理用到的范围，避免整体遍历导致超时
    for i in range(1, n + 1):
        head[i] = 0
        indegree[i] = 0


def add_edge(f, t):
    """
    用链式前向星建图
    """
    global cnt
    next_edge[cnt] = head[f]
    to[cnt] = t
    head[f] = cnt
    cnt += 1


def topo_sort(n):
    """
    字典序最小的拓扑排序
    """
    # 替代 Java 版本的手写堆，直接使用内置的 heapq 模块
    heap = []
    
    # 1. 寻找初始入度为 0 的点入堆
    for i in range(1, n + 1):
        if indegree[i] == 0:
            heapq.heappush(heap, i)
            
    fill = 0
    # 2. 不断从小根堆弹出节点，并解除相邻节点的入度
    while heap:
        cur = heapq.heappop(heap)
        ans[fill] = cur
        fill += 1
        
        # 用链式前向星的方式，遍历 cur 的相邻节点
        ei = head[cur]
        while ei != 0:
            v = to[ei]
            indegree[v] -= 1
            if indegree[v] == 0:
                heapq.heappush(heap, v)
            ei = next_edge[ei]


def main():
    # 竞赛中极速 I/O 读取方式
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    # 模拟 while (in.nextToken() != StreamTokenizer.TT_EOF)
    while idx < len(input_data):
        n = int(input_data[idx])
        m = int(input_data[idx + 1])
        idx += 2
        
        build(n)
        
        for _ in range(m):
            f = int(input_data[idx])
            t = int(input_data[idx + 1])
            idx += 2
            add_edge(f, t)
            indegree[t] += 1
            
        topo_sort(n)
        
        # 收集结果并快速输出
        # ans[:n] 截取前 n 个结果，转换为字符串后按空格拼接
        sys.stdout.write(" ".join(map(str, ans[:n])) + "\n")


if __name__ == '__main__':
    main()