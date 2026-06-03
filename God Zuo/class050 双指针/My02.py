#测试链接 : https://leetcode.cn/problems/find-the-duplicate-number/
from typing import List

class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        if not nums or len(nums)<2:
            return -1
        slow=nums[0]
        fast=nums[nums[0]]
        while slow != fast:
            slow=nums[slow]
            fast=nums[nums[fast]]
        fast=0
        while slow != fast:
            slow=nums[slow]
            fast=nums[fast]
        return fast