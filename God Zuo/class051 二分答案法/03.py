import sys

def solve():
    # 读入所有输入，切分后直接转化为迭代器
    tokens = iter(sys.stdin.read().split())
    
    while True:
        # 尝试获取下一个 token（N）。如果拿不到，说明文件读完了 (EOF)，直接退出循环
        n_str = next(tokens, None)
        if n_str is None:
            break
            
        n = int(n_str)
        
        arr = []
        max_h = 0
        for _ in range(n):
            # 直接使用 next(tokens) 拿数据，不用再管什么下标了
            val = int(next(tokens))
            arr.append(val)
            if val > max_h:
                max_h = val
                
        def check(energy: int) -> bool:
            for h in arr:
                energy = 2 * energy - h
                if energy >= max_h:
                    return True
                if energy < 0:
                    return False
            return True

        l, r = 0, max_h
        ans = -1
        while l <= r:
            m = (l + r) // 2
            if check(m):
                ans = m
                r = m - 1
            else:
                l = m + 1
                
        print(ans)

if __name__ == '__main__':
    solve()