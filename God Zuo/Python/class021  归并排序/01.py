# 归并排序，acm练习风格
# 测试链接 : https://www.luogu.com.cn/problem/P1177
# Python 版本 - 高效输入输出

import sys

# ------------------------------
# 全局变量
# ------------------------------
MAXN = 100001
arr = [0] * MAXN
help_arr = [0] * MAXN
n = 0


def merge(l: int, m: int, r: int) -> None:
    """合并 l...m 和 m+1...r 两段有序区间"""
    i = l
    a = l
    b = m + 1
    
    while a <= m and b <= r:
        if arr[a] <= arr[b]:
            help_arr[i] = arr[a]
            a += 1
        else:
            help_arr[i] = arr[b]
            b += 1
        i += 1
    
    # 剩余部分
    while a <= m:
        help_arr[i] = arr[a]
        a += 1
        i += 1
    
    while b <= r:
        help_arr[i] = arr[b]
        b += 1
        i += 1
    
    # 写回原数组
    for i in range(l, r + 1):
        arr[i] = help_arr[i]


def merge_sort1(l: int, r: int) -> None:
    """递归版归并排序"""
    if l == r:
        return
    m = (l + r) // 2
    merge_sort1(l, m)
    merge_sort1(m + 1, r)
    merge(l, m, r)


def merge_sort2() -> None:
    """非递归版归并排序（自底向上）"""
    step = 1
    while step < n:
        l = 0
        while l < n:
            m = l + step - 1
            if m + 1 >= n:
                break
            r = min(l + (step << 1) - 1, n - 1)
            merge(l, m, r)
            l = r + 1
        step <<= 1


def main():
    global n
    
    # 高效输入
    input = sys.stdin.read
    data = input().split()
    
    index = 0
    n = int(data[index])
    index += 1
    
    for i in range(n):
        arr[i] = int(data[index])
        index += 1
    
    # 两种写法任选其一
    # merge_sort1(0, n-1)          # 递归版
    merge_sort2()                   # 非递归版（推荐用于大数据，防止栈溢出）
    
    # 输出
    print(' '.join(map(str, arr[:n])))


if __name__ == "__main__":
    main()