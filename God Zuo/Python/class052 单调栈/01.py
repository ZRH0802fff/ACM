import sys

def main():
    # 快速 IO：一次性读取所有内容并按空白字符分割
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    # 转换为整数迭代器，相比逐个转换效率更高
    iterator = map(int, input_data)
    
    try:
        while True:
            # 尝试获取数组长度 n
            n = next(iterator)
            
            # 连续获取 n 个元素构成数组
            arr = [next(iterator) for _ in range(n)]
            
            # 使用两个一维数组代替二维数组，极大降低 Python 中的对象创建开销
            ans_l = [-1] * n
            ans_r = [-1] * n
            
            # Python 原生列表直接作为栈，底层优化极佳
            stack = []
            
            # 遍历阶段
            for i in range(n):
                # i -> arr[i]
                while stack and arr[stack[-1]] >= arr[i]:
                    cur = stack.pop()
                    # cur当前弹出的位置，左边最近且小
                    ans_l[cur] = stack[-1] if stack else -1
                    ans_r[cur] = i
                stack.append(i)
            
            # 清算阶段
            while stack:
                cur = stack.pop()
                ans_l[cur] = stack[-1] if stack else -1
                ans_r[cur] = -1
            
            # 修正阶段
            # 左侧的答案不需要修正，一定是正确的；只有右侧答案需要修正
            # 从右往左修正，n-1位置的右侧答案一定是-1，不需要修正
            for i in range(n - 2, -1, -1):
                if ans_r[i] != -1 and arr[ans_r[i]] == arr[i]:
                    ans_r[i] = ans_r[ans_r[i]]
            
            # 输出阶段：将结果收集后一次性输出，减少 IO 调用次数
            out = []
            for i in range(n):
                out.append(f"{ans_l[i]} {ans_r[i]}")
            sys.stdout.write('\n'.join(out) + '\n')
            
    except StopIteration:
        # 迭代器耗尽，说明输入处理完毕，正常退出
        pass

if __name__ == '__main__':
    main()