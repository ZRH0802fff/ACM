#测试链接 : https://leetcode.cn/problems/minimum-size-subarray-sum/
from typing import List

class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        ans=float('inf')
        l=0
        sum_=0
        for r in range(len(nums)):
            sum_+=nums[r]
            while sum_-nums[l]>=target:
                sum_-=nums[l]
                l+=1
            if sum_>=target:
                ans=min(ans,r-l+1)
        return 0 if ans == float('inf') else ans 