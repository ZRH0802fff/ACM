#测试链接 : https://leetcode.cn/problems/trapping-rain-water/
from typing import List

class Solution:
    def trap1(self, nums: List[int]) -> int:
        n=len(nums)
        lmax=[0]*n
        rmax=[0]*n
        lmax[0] = nums[0]
        for i in range(1, n):
            lmax[i] = max(lmax[i - 1], nums[i])
        rmax[n - 1] = nums[n - 1]
        for i in range(n - 2, -1, -1):
            rmax[i] = max(rmax[i + 1], nums[i])          
        ans = 0
        for i in range(1, n - 1):
            ans += max(0, min(lmax[i - 1], rmax[i + 1]) - nums[i])     
        return ans
    def trap2(self, nums: List[int]) -> int:
        l = 1
        r = len(nums) - 2
        lmax = nums[0]
        rmax = nums[-1]
        ans = 0
        while l<=r:
            if lmax<=rmax:
                ans+=max(0,lmax-nums[l])
                lmax=max(nums[l],lmax)
                l+=1
            else:
                ans+=max(0,rmax-nums[r])
                rmax=max(rmax,nums[r])
                r+=1
        return ans