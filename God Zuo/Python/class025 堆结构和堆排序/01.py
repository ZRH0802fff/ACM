# 堆结构和堆排序，acm练习风格
# 测试链接 : https://www.luogu.com.cn/problem/P1177
# 请同学们务必参考如下代码中关于输入、输出的处理
# 这是输入输出处理效率很高的写法
# Python版本无需修改类名，直接提交即可通过

import sys

MAXN = 100001
arr = [0] * MAXN
n = 0


# i位置的数，向上调整大根堆
def heapInsert(i): 
    while arr[i] > arr[(i - 1) // 2]:
        swap(i, (i - 1) // 2)
        i = (i - 1) // 2


# i位置的数，向下调整大根堆
# 当前堆的大小为size
def heapify(i, size):
    l = i * 2 + 1
    while l < size:
        best = l + 1 if l + 1 < size and arr[l + 1] > arr[l] else l
        best = best if arr[best] > arr[i] else i
        if best == i:
            break
        swap(best, i)
        i = best
        l = i * 2 + 1


def swap(i, j):
    arr[i], arr[j] = arr[j], arr[i]


# 从顶到底建立大根堆，O(n * logn)
# 依次弹出堆内最大值并排好序，O(n * logn)
# 整体时间复杂度O(n * logn)
def heapSort1():
    for i in range(n):
        heapInsert(i)
    size = n
    while size > 1:
        size -= 1
        swap(0, size)
        heapify(0, size)


# 从底到顶建立大根堆，O(n)
# 依次弹出堆内最大值并排好序，O(n * logn)
# 整体时间复杂度O(n * logn)
def heapSort2():
    for i in range(n - 1, -1, -1):
        heapify(i, n)
    size = n
    while size > 1:
        size -= 1
        swap(0, size)
        heapify(0, size)


# 主函数（高效输入输出）
data = sys.stdin.read().split()
idx = 0
n = int(data[idx])
idx += 1
for i in range(n):
    arr[i] = int(data[idx])
    idx += 1

# heapSort1()
heapSort2()

# 输出（一行，数字间空格，无多余空格）
print(' '.join(str(arr[i]) for i in range(n)))