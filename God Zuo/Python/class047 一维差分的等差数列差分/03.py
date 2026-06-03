import sys

# 一群人落水后求每个位置的水位高度
# 测试链接 : https://www.luogu.com.cn/problem/P5026

MAXN = 1000001
OFFSET = 30001

# 准备足够大的数组
arr = [0] * (OFFSET + MAXN + OFFSET)

def fall(v, x):
    set_val(x - 3 * v + 1, x - 2 * v, 1, v, 1)
    set_val(x - 2 * v + 1, x, v - 1, -v, -1)
    set_val(x + 1, x + 2 * v, -v + 1, v, 1)
    set_val(x + 2 * v + 1, x + 3 * v - 1, v - 1, 1, -1)

def set_val(l, r, s, e, d):
    # 加上 OFFSET 防止负数下标
    arr[l + OFFSET] += s
    arr[l + 1 + OFFSET] += d - s
    arr[r + 1 + OFFSET] -= d + e
    arr[r + 2 + OFFSET] += e

def build(m):
    # 第一次前缀和
    for i in range(1, m + OFFSET + 1):
        arr[i] += arr[i - 1]
    # 第二次前缀和（因为是二次差分）
    for i in range(1, m + OFFSET + 1):
        arr[i] += arr[i - 1]

def main():
    input = sys.stdin.read
    data = input().split()
    
    index = 0
    while index < len(data):
        n = int(data[index])
        index += 1
        m = int(data[index])
        index += 1
        
        # 重置数组（因为可能有多组测试数据）
        global arr
        arr = [0] * (OFFSET + MAXN + OFFSET)
        
        for _ in range(n):
            v = int(data[index])
            index += 1
            x = int(data[index])
            index += 1
            fall(v, x)
        
        build(m)
        
        # 输出正式位置 1 到 m 的水位
        # 正式位置对应 arr[OFFSET + 1] 到 arr[OFFSET + m]
        result = [str(arr[OFFSET + i]) for i in range(1, m + 1)]
        print(' '.join(result))

if __name__ == "__main__":
    main()