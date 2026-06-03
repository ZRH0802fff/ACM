import sys

# 小和问题，Python版
# 测试链接 : https://www.nowcoder.com/practice/edfe05a1d45c4ea89101d936cac32469
# 请同学们务必参考如下代码中关于输入、输出的处理
# 这是输入输出处理效率很高的写法
# 提交时直接使用下面代码即可

MAXN = 100001
arr = [0] * MAXN
temp = [0] * MAXN


# 结果比较大，Python的int不会溢出
# 返回arr[l...r]范围上，小和的累加和，同时请把arr[l..r]变有序
# 时间复杂度O(n * logn)
def smallSum(l, r):
    if l == r:
        return 0
    m = (l + r) // 2
    return smallSum(l, m) + smallSum(m + 1, r) + merge(l, m, r)


# 返回跨左右产生的小和累加和，左侧有序、右侧有序，让左右两侧整体有序
# arr[l...m] arr[m+1...r]
def merge(l, m, r):
    # 统计部分
    ans = 0
    i = l 
    sum_val = 0
    for j in range(m + 1, r + 1):
        while i <= m and arr[i] <= arr[j]:
            sum_val += arr[i]
            i += 1
        ans += sum_val

    # 正常merge
    i = l
    a = l
    b = m + 1
    while a <= m and b <= r:
        if arr[a] <= arr[b]:
            temp[i] = arr[a]
            a += 1
        else:
            temp[i] = arr[b]
            b += 1
        i += 1
    while a <= m:
        temp[i] = arr[a]
        a += 1
        i += 1
    while b <= r:
        temp[i] = arr[b]
        b += 1
        i += 1
    for k in range(l, r + 1):
        arr[k] = temp[k]

    return ans


# 高效输入处理（支持多组数据直到EOF）
data = sys.stdin.read().split()
idx = 0
while idx < len(data):
    n = int(data[idx])
    idx += 1
    for i in range(n):
        arr[i] = int(data[idx])
        idx += 1
    print(smallSum(0, n - 1))