# 测试链接 : https://leetcode.cn/problems/maximum-running-time-of-n-computers/
from typing import List

class Solution:
    def maxRunTime1(self, n: int, batteries: List[int]) -> int:
        def f(t):
            td,tco=0,n
            for num in batteries:
                if num>=t:
                    tco-=1
                else:
                    td+=num
                if td>=tco*t:
                    return True
            return False
        l,r,ans=0,sum(batteries),0
        while l<=r:
            m=(l+r)//2
            if f(m):
                ans=m
                l=m+1
            else:
                r=m-1
        return ans
    def maxRunTime2(self, n: int, batteries: List[int]) -> int:
        def f(t):
            td,tco=0,n
            for num in batteries:
                if num>=t:
                    tco-=1
                else:
                    td+=num
                if td>=tco*t:
                    return True
            return False
        sum_ba=sum(batteries)
        max_ba=max(batteries)
        if sum_ba>=max_ba*n:
            return sum_ba//n
        l,r,asn=0,max_ba,0
        while l<=r:
            m=(l+r)//2
            if f(m):
                ans=m
                l=m+1
            else:
                r=m-1
        return ans