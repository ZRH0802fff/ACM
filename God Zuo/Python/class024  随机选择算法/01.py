# 无序数组中第K大的元素
# 测试链接 : https://leetcode.cn/problems/kth-largest-element-in-an-array/
import random


class RandomizedSelect:

    first = 0
    last = 0

    # 随机选择算法，时间复杂度O(n)
    @staticmethod
    def findKthLargest(nums, k):
        return RandomizedSelect.randomizedSelect(nums, len(nums) - k)

    # 如果arr排序的话，在i位置的数字是什么
    @staticmethod
    def randomizedSelect(arr, i):
        ans = 0
        l = 0
        r = len(arr) - 1
        while l <= r:
            # 随机这一下，常数时间比较大
            # 但只有这一下随机，才能在概率上把时间复杂度收敛到O(n)
            idx = l + random.randint(0, r - l)
            RandomizedSelect.partition(arr, l, r, arr[idx])
            # 因为左右两侧只需要走一侧
            # 所以不需要临时变量记录全局的first、last
            # 直接用即可
            if i < RandomizedSelect.first:
                r = RandomizedSelect.first - 1
            elif i > RandomizedSelect.last:
                l = RandomizedSelect.last + 1
            else:
                ans = arr[i]
                break
        return ans

    # 荷兰国旗问题
    @staticmethod
    def partition(arr, l, r, x):
        RandomizedSelect.first = l
        RandomizedSelect.last = r
        i = l
        while i <= RandomizedSelect.last:
            if arr[i] == x:
                i += 1
            elif arr[i] < x:
                RandomizedSelect.swap(arr, RandomizedSelect.first, i)
                RandomizedSelect.first += 1
                i += 1
            else:
                RandomizedSelect.swap(arr, i, RandomizedSelect.last)
                RandomizedSelect.last -= 1

    @staticmethod
    def swap(arr, i, j):
        tmp = arr[i]
        arr[i] = arr[j]
        arr[j] = tmp