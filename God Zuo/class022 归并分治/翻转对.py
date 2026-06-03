# 翻转对数量
# 测试链接 : https://leetcode.cn/problems/reverse-pairs/
MAXN = 50001
help = [0] * MAXN


def reversePairs(arr):
    return counts(arr, 0, len(arr) - 1)


# 统计l...r范围上，翻转对的数量，同时l...r范围统计完后变有序
# 时间复杂度O(n * logn)
def counts(arr, l, r):
    if l == r:
        return 0
    m = (l + r) // 2
    return counts(arr, l, m) + counts(arr, m + 1, r) + merge(arr, l, m, r)


def merge(arr, l, m, r):
    # 统计部分
    ans = 0
    j = m + 1
    for i in range(l, m + 1):
        while j <= r and arr[i] > arr[j] * 2:
            j += 1
        ans += j - m - 1

    # 正常merge
    pos = l
    a = l
    b = m + 1
    while a <= m and b <= r:
        if arr[a] <= arr[b]:
            help[pos] = arr[a]
            a += 1
        else:
            help[pos] = arr[b]
            b += 1
        pos += 1
    while a <= m:
        help[pos] = arr[a]
        a += 1
        pos += 1
    while b <= r:
        help[pos] = arr[b]
        b += 1
        pos += 1

    for i in range(l, r + 1):
        arr[i] = help[i]

    return ans