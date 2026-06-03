import random

# 为了验证
def random_array(n, v):
    return [int(random.random() * v) + 1 for _ in range(n)]


# 为了验证（暴力）
# 有序数组中找 >= num 的最左位置
def right(arr, num):
    for i in range(len(arr)):
        if arr[i] >= num:
            return i
    return -1


# 有序数组中找 >= num 的最左位置（二分）
def find_left(arr, num):
    l, r = 0, len(arr) - 1
    ans = -1
    while l <= r:
        m = l + ((r - l) >> 1)
        if arr[m] >= num:
            ans = m     #ans记录下答案的位置并不断向左找新答案
            r = m - 1
        else:
            l = m + 1
    return ans


# ================== 对数器（原 main 内容） ==================

N = 100
V = 1000
testTime = 500000

print("测试开始")

for _ in range(testTime):
    n = int(random.random() * N)
    arr = random_array(n, V)
    arr.sort()
    num = int(random.random() * V)

    if right(arr, num) != find_left(arr, num):
        print("出错了!")
        print("arr =", arr)
        print("num =", num)
        print("right =", right(arr, num))
        print("find_left =", find_left(arr, num))
        break

print("测试结束")
