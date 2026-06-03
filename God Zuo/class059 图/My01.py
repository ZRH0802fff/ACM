#邻接矩阵建图
MAXN=11
book1=[[0]*MAXN for _ in range(MAXN)]
def clear1(n):
    for i in range(1,n+1):
        for j in range(1,n+1):
            book1[i][j]=0
def yx1(edges):
    for u,v,w in edges:
        book1[u][v]=w
def wx1(edges):
    for u,v,w in edges:
        book1[u][v]=w
        book1[v][u]=w
def print1(n):
    for i in range(1,n+1):
        print(' '.join(str(book1[i][j]) for j in range(1,n+1)))

#邻接表建图
book2=[]
def clear2(n):
    global book2
    book2=[[] for _ in range(n+1)]
def yx2(edges):
    for u,v,w in edges:
        book2[u].append((v,w))
def wx2(edges):
    for u,v,w in edges:
        book2[u].append((v,w))
        book2[v].append((u,w))
def print2(n):
    for i in range(1,n+1):
        print(f"{i}(邻居，边权): " , end="")
        for v,w in book2[i]:
            print(f"({v} , {w})", end='')
        print()

#链式前向星建图
MAXM=21
head=[0]*MAXM
nxt=[0]*MAXM
to=[0]*MAXM
weight=[0]*MAXM
cnt=1
def clear3(n):
    global cnt
    cnt=1
    for i in range(1,n+1):
        head[i]=0
def add_edges(u,v,w):
    global cnt
    nxt[cnt]=head[u]
    to[cnt]=v
    weight[cnt]=w
    head[u]=cnt
    cnt+=1
def yx3(edges):
    for u,v,w in edges:
        add_edges(u,v,w)
def wx3(edges):
    for u,v,w in edges:
        add_edges(u,v,w)
        add_edges(v,u,w)
def print3(n):
    for i in range(1,n+1):
        print(f"{i}邻居，边权： " , end='')
        t=head[i]
        while t !=0:
            print(f"({to[t]},{weight[t]})" , end='')
            t=nxt[t]
        print()

def test_graph():
    print("====== 测试有向带权图 ======")
    n1 = 4
    edges1 = [[1, 3, 6], [4, 3, 4], [2, 4, 2], [1, 2, 7], [2, 3, 5], [3, 1, 1]]
    
    print("\n--- 邻接矩阵 ---")
    clear1(n1)
    yx1(edges1)
    print1(n1)

    print("\n--- 邻接表 ---")
    clear2(n1)
    yx2(edges1)
    print2(n1)

    print("\n--- 链式前向星 ---")
    clear3(n1)
    yx3(edges1)
    print3(n1)

    print("\n\n====== 测试无向带权图 ======")
    n2 = 5
    edges2 = [[3, 5, 4], [4, 1, 1], [3, 4, 2], [5, 2, 4], [2, 3, 7], [1, 5, 5], [4, 2, 6]]

    print("\n--- 邻接矩阵 ---")
    clear1(n2)
    wx1(edges2)
    print1(n2)

    print("\n--- 邻接表 ---")
    clear2(n2)
    wx2(edges2)
    print2(n2)

    print("\n--- 链式前向星 ---")
    clear3(n2)
    wx3(edges2)
    print3(n2)


if __name__ == "__main__":
    test_graph()