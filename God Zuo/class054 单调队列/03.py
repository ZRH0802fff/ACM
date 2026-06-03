import sys

def solve():
    # 模拟 Java 的 StreamTokenizer 行为，一次性读取所有输入并以空格/换行切分
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    idx = 0
    n_tokens = len(input_data)
    
    # 类似 Java 的 while (in.nextToken() != StreamTokenizer.TT_EOF)
    while idx < n_tokens:
        n = int(input_data[idx])
        d = int(input_data[idx+1])
        idx += 2
        
        # 收集水滴的 x坐标 和 高度y
        arr = []
        for _ in range(n):
            arr.append((int(input_data[idx]), int(input_data[idx+1])))
            idx += 2
            
        # 所有水滴根据 x 坐标排序，谁小谁在前
        arr.sort(key=lambda x: x[0])
        
        # 模拟双端队列
        max_q = [0] * n
        min_q = [0] * n
        max_h = max_t = 0
        min_h = min_t = 0
        
        # 判断当前窗口的 最大高度 - 最小高度 是否 >= d
        def ok():
            max_val = arr[max_q[max_h]][1] if max_h < max_t else 0
            min_val = arr[min_q[min_h]][1] if min_h < min_t else 0
            return max_val - min_val >= d

        def push(r):
            nonlocal max_t, min_t
            # 维护最大值单调队列 (递减)
            while max_h < max_t and arr[max_q[max_t - 1]][1] <= arr[r][1]:
                max_t -= 1
            max_q[max_t] = r
            max_t += 1
            
            # 维护最小值单调队列 (递增)
            while min_h < min_t and arr[min_q[min_t - 1]][1] >= arr[r][1]:
                min_t -= 1
            min_q[min_t] = r
            min_t += 1

        def pop(l):
            nonlocal max_h, min_h
            # 如果即将滑出窗口的元素是队列头，则将队列头指针右移
            if max_h < max_t and max_q[max_h] == l:
                max_h += 1
            if min_h < min_t and min_q[min_h] == l:
                min_h += 1

        ans = float('inf')
        r = 0
        
        # 滑动窗口主逻辑
        for l in range(n):
            # [l, r) : 窗口内水滴的编号
            # arr[l][0] : 当前花盆的左边界
            while not ok() and r < n:
                push(r)
                r += 1
                
            if ok():
                ans = min(ans, arr[r - 1][0] - arr[l][0])
                
            pop(l)
            
        # 输出结果
        if ans == float('inf'):
            print("-1")
        else:
            print(ans)

if __name__ == '__main__':
    solve()