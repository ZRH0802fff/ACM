# 测试链接 : https://leetcode.cn/problems/maximum-width-ramp/
class Solution:
    def maxWidthRamp(self, nums: list[int]) -> int:
        n=len(nums)
        stack=[]
        ans=0
        stack.append(0)
        for i in range(1,n):
            if nums[i]<nums[stack[-1]]:
                stack.append(i)
        for i in range(n-1,-1,-1):
            while stack and nums[stack[-1]]<=nums[i]:
                t = stack.pop()
                width = i - i
                if width > ans:
                    ans = width
        return ans
    