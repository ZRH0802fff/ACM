from typing import List

# 利用前缀和快速得到区域累加和
# 测试链接 : https://leetcode.cn/problems/range-sum-query-immutable/
class NumArray:

    def __init__(self, nums: List[int]):
        self.sum = [0] * (len(nums) + 1)
        for i in range(1, len(nums) + 1):
            self.sum[i] = self.sum[i - 1] + nums[i - 1]

    def sumRange(self, left: int, right: int) -> int:
        return self.sum[right + 1] - self.sum[left]