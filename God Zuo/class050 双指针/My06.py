# 测试链接 : https://leetcode.cn/problems/heaters/
from typing import List

class Solution:
    def findRadius(self, houses: List[int], heaters: List[int]) -> int:
        houses.sort()
        heaters.sort()
        j=0
        ans=0
        m=len(heaters)
        for ch in houses:
            while j<m-1 and abs(heaters[j]-ch)>=abs(heaters[j+1]-ch):
                j+=1
            ans=max(ans,abs(heaters[j]-ch))
        return ans