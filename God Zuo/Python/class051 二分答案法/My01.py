# 测试链接 : https://leetcode.cn/problems/koko-eating-bananas/
from typing import List

class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        val_max=max(piles)
        l,r=1,val_max
        ans=0
        def f (sp):
            return sum((_+sp-1)//sp for _ in piles)
        while l<=r :
            m=(l+r)//2
            if f(m)<=h:
                ans=m
                r=m-1
            else:
                l=m+1
        return ans