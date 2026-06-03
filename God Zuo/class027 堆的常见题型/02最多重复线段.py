# 最多线段重合问题
# 测试链接 : https://www.nowcoder.com/practice/1ae8d0b6bb4e4bcdbf64ec491f63fc37
# 测试链接 : https://leetcode.cn/problems/meeting-rooms-ii/
# 提交以下的code，提交时请把类名改成"Main"，可以直接通过

import sys
import heapq

# 全局变量
MAXN = 10001
line = [[0, 0] for _ in range(MAXN)]
n = 0
# 小根堆，直接用列表和heapq模块实现
heap = []


def compute():
    global line, n, heap
    
    # 堆的清空
    heap = []

    # 线段一共有n条，line[0...n-1][2] : line[i][0] line[i][1], 左闭右闭
    # 所有线段，根据开始位置排序，结束位置无所谓
    # 排序: 所有线段，开始位置谁小谁在前
    line[:n] = sorted(line[:n], key=lambda x: x[0])
    
    ans = 0
    for i in range(n):
        # i : line[i][0] line[i][1]
        while heap and heap[0] <= line[i][0]:
            heapq.heappop(heap)  # heapq自带的pop方法
        heapq.heappush(heap, line[i][1])  # heapq自带的add方法（push）
        ans = max(ans, len(heap))
    return ans


# 也找到了leetcode测试链接
# 测试链接 : https://leetcode.cn/problems/meeting-rooms-ii/
# 提交如下代码可以直接通过
def minMeetingRooms(meeting):
    n = len(meeting)
    meeting.sort(key=lambda x: x[0])  # 按开始时间排序
    heap = []  # Python的小根堆
    ans = 0
    for i in range(n):
        while heap and heap[0] <= meeting[i][0]:
            heapq.heappop(heap)  # heapq自带的pop方法
        heapq.heappush(heap, meeting[i][1])  # heapq自带的add方法（push）
        ans = max(ans, len(heap))
    return ans


# 上面的leetcode题目是会员题，需要付费
# 如果不想开通leetcode会员，还有一个类似的题，但是注意题意，和课上讲的有细微差别
# 课上讲的题目，认为[1,4]、[4、5]可以严丝合缝接在一起，不算有重合
# 但是如下链接的题目，认为[1,4]、[4、5]有重合部分，也就是4
# 除此之外别无差别
# 测试链接 : https://leetcode.cn/problems/divide-intervals-into-minimum-number-of-groups/
# 提交如下代码可以直接通过
def minGroups(meeting):
    n = len(meeting)
    meeting.sort(key=lambda x: x[0])  # 按开始时间排序
    heap = []  # Python的小根堆
    ans = 0
    for i in range(n):
        # 注意这里的判断
        while heap and heap[0] < meeting[i][0]:
            heapq.heappop(heap)  # heapq自带的pop方法
        heapq.heappush(heap, meeting[i][1])  # heapq自带的add方法（push）
        ans = max(ans, len(heap))
    return ans


# 主程序逻辑
input_data = sys.stdin.read().strip().split()
idx = 0
out_lines = []

while idx < len(input_data):
    n = int(input_data[idx])
    idx += 1
    for i in range(n):
        line[i][0] = int(input_data[idx])
        idx += 1
        line[i][1] = int(input_data[idx])
        idx += 1
    out_lines.append(str(compute()))

sys.stdout.write("\n".join(out_lines))

def add(x):
    """向小根堆中添加元素"""
    global size, heap
    
    heap[size] = x
    i = size
    size += 1
    
    # 向上调整堆
    while i > 0 and heap[i] < heap[(i - 1) // 2]:
        swap(i, (i - 1) // 2)
        i = (i - 1) // 2


def pop():
    """弹出堆顶元素"""
    global size, heap
    
    swap(0, size - 1)
    size -= 1
    
    # 向下调整堆
    i = 0
    l = 1  # 左孩子索引
    while l < size:
        # 找出左右孩子中较小的那个
        best = l
        if l + 1 < size and heap[l + 1] < heap[l]:
            best = l + 1
        
        # 如果孩子比当前节点小，则需要交换
        if heap[best] < heap[i]:
            swap(i, best)
            i = best
            l = i * 2 + 1
        else:
            break

def swap(i, j):
    """交换堆中的两个元素"""
    global heap
    heap[i], heap[j] = heap[j], heap[i]