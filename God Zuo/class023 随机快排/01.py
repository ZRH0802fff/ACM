import sys
import random

# 随机快速排序，acm练习风格
# 测试链接 : https://www.luogu.com.cn/problem/P1177
# 请同学们务必参考如下代码中关于输入、输出的处理
# 这是输入输出处理效率很高的写法
# 提交以下的code，可以直接通过

MAXN = 100001

arr = [0] * MAXN
n = 0
first = 0
last = 0


def swap(i, j):
    arr[i], arr[j] = arr[j], arr[i]


# 随机快速排序经典版(不推荐)
# 甚至在洛谷上测试因为递归开太多层会爆栈导致出错
def quickSort1(l, r):
    # l == r，只有一个数
    # l > r，范围不存在，不用管
    if l >= r:
        return
    # 随机这一下，常数时间比较大
    # 但只有这一下随机，才能在概率上把快速排序的时间复杂度收敛到O(n * logn)
    # l......r 随机选一个位置，x这个值，做划分
    x = arr[l + int(random.random() * (r - l + 1))]
    mid = partition1(l, r, x)
    quickSort1(l, mid - 1)
    quickSort1(mid + 1, r)


# 已知arr[l....r]范围上一定有x这个值
# 划分数组 <=x放左边，>x放右边
# 并且确保划分完成后<=x区域的最后一个数字是x
def partition1(l, r, x):
    # a : arr[l....a-1]范围是<=x的区域
    # xi : 记录在<=x的区域上任何一个x的位置，哪一个都可以
    a = l
    xi = 0
    for i in range(l, r + 1):
        if arr[i] <= x:
            swap(a, i)
            if arr[a] == x:
                xi = a
            a += 1
    swap(xi, a - 1)
    return a - 1


# 随机快速排序改进版(推荐)
# 可以通过所有测试用例
def quickSort2(l, r):
    if l >= r:
        return
    # 随机这一下，常数时间比较大
    # 但只有这一下随机，才能在概率上把快速排序的时间复杂度收敛到O(n * logn)
    x = arr[l + int(random.random() * (r - l + 1))]
    partition2(l, r, x)
    # 为了防止底层的递归过程覆盖全局变量
    # 这里用临时变量记录first、last
    left = first
    right = last
    quickSort2(l, left - 1)
    quickSort2(right + 1, r)


# 荷兰国旗问题
def partition2(l, r, x):
    # 已知arr[l....r]范围上一定有x这个值
    # 划分数组 <x放左边，==x放中间，>x放右边
    # 把全局变量first, last，更新成==x区域的左右边界
    global first, last
    first = l
    last = r
    i = l
    while i <= last:
        if arr[i] == x:
            i += 1
        elif arr[i] < x:
            swap(first, i)
            first += 1
            i += 1
        else:
            swap(i, last)
            last -= 1


if __name__ == "__main__":
    # 高效输入（等价于Java的StreamTokenizer）
    data = sys.stdin.read().split()
    idx = 0
    n = int(data[idx])
    idx += 1
    for i in range(n):
        arr[i] = int(data[idx])
        idx += 1

    quickSort2(0, n - 1)

    # 高效输出（无多余空格）
    print(' '.join(str(arr[i]) for i in range(n)))