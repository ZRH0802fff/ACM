# 测试链接 : https://leetcode.cn/problems/boats-to-save-people/
from typing import List

class Solution:
    def numRescueBoats(self, people: List[int], limit: int) -> int:
        people.sort()
        l,r=0,len(people)-1
        ans=0
        while l<r:
            if people[l]+people[r]>limit:
                r-=1
                ans+=1
            else:
                l+=1
                r-=1
                ans+=1
        if l==r:
            ans+=1
        return ans