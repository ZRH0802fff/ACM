#测试链接 : https://leetcode.cn/problems/subarrays-with-k-different-integers/
from typing import List

class Solution:
    def subarraysWithKDistinct(self, nums: List[int], k: int) -> int:
        def f (k):
            n=len(nums)
            countbok=[0]*(n+5)
            ans,l,numvary=0,0,0
            for r in range(n):
                if countbok[nums[r]]==0:
                    numvary+=1
                countbok[nums[r]]+=1
                while numvary>k:
                    countbok[nums[l]]-=1
                    if countbok[nums[l]]==0:
                        numvary-=1
                    l+=1
                ans+=r-l+1
            return  ans
        return f(k)-f(k-1)
                