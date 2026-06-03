# 测试链接 : https://leetcode.cn/problems/split-array-largest-sum/
from typing import List

class Solution:
    def splitArray(self, nums: List[int], k: int) -> int: 
        l,r,ans=0,sum(nums),0
        def f (lit):
            ans,t_sum=0,0
            for num in nums:
                if num>lit:
                    return float('inf')
                if num+t_sum>lit:
                    ans+=1
                    t_sum=num
                else:
                    t_sum+=num
            return ans
        while l<=r:  
            m=(l+r)//2
            if f(m)<=k:
                ans=m
                r=m-1
            else:
                l=m+1
        return ans