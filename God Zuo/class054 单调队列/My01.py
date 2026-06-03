#https://leetcode.cn/problems/sliding-window-maximum/description/
class Solution:
    def maxSlidingWindow(self, nums, k: int):
        n=len(nums)
        deque=[0]*n
        h=t=0
        for i in range(k-1):
            while h<t and nums[i]>nums[deque[t-1]]:
                t-=1
            deque[t]=i
            t+=1
        m=n-k+1
        ans=[0]*m
        for l in range(m):
            r=l+k-1
            while h<t and nums[r]>=nums[deque[t-1]]:
                t-=1
            deque[t]=r
            t+=1
            ans[l]=nums[deque[h]]
            if deque[h]==l:
                h+=1
        return ans
