import sys

def solve():
    # 一次性读取所有的输入，按照空白字符（空格、换行）分割
    # 这是 Python 中替代 StreamTokenizer 最快、最 Pythonic 的做法
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    # 使用迭代器方便逐个获取数据
    iterator = iter(input_data)
    
    try:
        while True:
            # 捕获异常来判断是否到达 EOF
            n = int(next(iterator))
            q = int(next(iterator))
            
            # 初始化二维差分数组
            # 尺寸为 (n + 2) x (n + 2)，防止 c+1 和 d+1 越界
            diff = [[0] * (n + 2) for _ in range(n + 2)]
            
            # 处理 q 次区间加操作
            for _ in range(q):
                a = int(next(iterator))
                b = int(next(iterator))
                c = int(next(iterator))
                d = int(next(iterator))
                
                # 差分数组打标 (这里直接内联，比单独写个 add 函数调用更快)
                diff[a][b] += 1
                diff[c + 1][b] -= 1
                diff[a][d + 1] -= 1
                diff[c + 1][d + 1] += 1
            
            # 准备输出的结果列表（用列表收集字符串然后一次性输出，比频繁调用 print 快很多）
            result = []
            
            # 利用前缀和还原原始矩阵，并同时收集输出结果
            for i in range(1, n + 1):
                for j in range(1, n + 1):
                    diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1]
                
                # 将第 i 行的 1 到 n 个元素转为字符串并用空格拼接
                result.append(" ".join(map(str, diff[i][1:n + 1])))
            
            # 统一输出
            sys.stdout.write("\n".join(result) + "\n")
            
    except StopIteration:
        # 当 next(iterator) 抛出 StopIteration 时，说明数据读完了 (EOF)
        pass

if __name__ == '__main__':
    solve()