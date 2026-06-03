import sys

def solve():
    # 1. 极致 Fast I/O：一次性读取所有内容并按空白字符分割
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    out = []
    
    # 应对多组测试数据的标准写法
    try:
        while True:
            n = int(next(iterator))
            m = int(next(iterator))
            
            # 2. C 级别极速初始化
            # father[i] = i
            father = list(range(n + 1))
            # size[i] = 1
            size = [1] * (n + 1)
            
            # 3. 闭包内联：直接操纵外层局部变量，避免 self 访问开销
            def find(i):
                # 迭代实现路径压缩，完美规避 Python 递归深度超限问题 (RecursionError)
                path = []
                while i != father[i]:
                    path.append(i)
                    i = father[i]
                # 沿途节点直接挂到代表节点 (根节点) 下面
                for node in path:
                    father[node] = i
                return i
                
            def union(x, y):
                fx = find(x)
                fy = find(y)
                if fx != fy:
                    # 小挂大策略：将节点数少的集合挂载到节点数多的集合下面
                    if size[fx] >= size[fy]:
                        size[fx] += size[fy]
                        father[fy] = fx
                    else:
                        size[fy] += size[fx]
                        father[fx] = fy
                        
            # 处理这组测试用例的 m 次操作
            for _ in range(m):
                op = int(next(iterator))
                x = int(next(iterator))
                y = int(next(iterator))
                
                if op == 1:
                    out.append("Yes" if find(x) == find(y) else "No")
                else:
                    union(x, y)
                    
    except StopIteration:
        # 当 next(iterator) 抛出异常时，说明所有输入读取完毕
        pass
        
    # 4. 批量输出，最后统一刷新缓冲区
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()