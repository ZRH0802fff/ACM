#测试链接 : https://leetcode.cn/problems/sort-array-by-parity-ii/
from typing import List

class Solution:
    def sortArrayByParityII(self, nums: List[int]) -> List[int]:
        n=len(nums)
        ou,ji = 0 ,1
        while ou<n and ji <n :
            if nums[-1]&1==1:
                nums[ji],nums[-1]=nums[-1],nums[ji]
                ji+=2
            else :
                nums[ou],nums[-1]=nums[-1],nums[ou]
                ou+=2
        return nums