# 测试链接 : https://leetcode.cn/problems/daily-temperatures/
from typing import List

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n=len(temperatures)
        ans=[0]*n
        stack=[]
        for i in range(n):
            while stack and temperatures[stack[-1]]<temperatures[i]:
                cur=stack.pop()
                ans[cur]=i-cur
            stack.append(i)
        return ans