import sys

MAXN = 10000005
arr = [0] * MAXN

def main():
    input = sys.stdin.read
    data = input().split()
    
    index = 0
    while index < len(data):
        n = int(data[index])
        index += 1
        m = int(data[index])
        index += 1
        
        # 清空数组（仅处理需要的范围）
        for i in range(1, n + 2):
            arr[i] = 0
        
        for _ in range(m):
            l = int(data[index])
            r = int(data[index + 1])
            s = int(data[index + 2])
            e = int(data[index + 3])
            index += 4
            
            # 计算公差 d = (e - s) / (r - l)，注意是整数除法
            d = (e - s) // (r - l)
            set_diff(l, r, s, e, d)
        
        build(n)
        
        max_val = 0
        xor_val = 0
        for i in range(1, n + 1):
            max_val = max(max_val, arr[i])
            xor_val ^= arr[i]
        
        print(xor_val, max_val)


def set_diff(l: int, r: int, s: int, e: int, d: int):
    """差分标记：对等差数列的差分处理"""
    arr[l] += s
    arr[l + 1] += d - s
    arr[r + 1] -= d + e
    arr[r + 2] += e


def build(n: int):
    """两次前缀和，还原最终数组"""
    # 第一次前缀和
    for i in range(1, n + 1):
        arr[i] += arr[i - 1]
    
    # 第二次前缀和
    for i in range(1, n + 1):
        arr[i] += arr[i - 1]


if __name__ == "__main__":
    main() 