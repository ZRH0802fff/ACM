# 测试链接 : https://leetcode.cn/problems/find-k-th-smallest-pair-distance/
from typing import List

class Solution:
    def smallestDistancePair(self, nums: List[int], k: int) -> int:
        nums.sort()
        l,r,ans=0,nums[0]-nums[-1],0
        n=len(nums)
        def f (ma):
            ans,r=0,0
            for l in range(n):
                while r<n and nums[r]-nums[l]<=ma:
                    r+=1
                ans+=r-l
            return ans
        while l<=r:
            m=(l+r)//2
            if f(m)>=k:
                ans=m
                l=m+1
            else:
                r=m-1
        return ans