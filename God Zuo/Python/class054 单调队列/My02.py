#测试链接 : https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
class Solution:
    def longestSubarray(self, nums: list[int], limit: int) -> int:
        n=len(nums)
        max_q = [0] * n
        min_q = [0] * n
        max_h = max_t = 0
        min_h = min_t = 0
        ans = 0
        r = 0
        def ok(limit,curr):
            max_val = nums[max_q[max_h]] if max_h < max_t and nums[max_q[max_h]] > curr else curr
            min_val = nums[min_q[min_h]] if min_h < min_t and nums[min_q[min_h]] < curr else curr
            return max_val - min_val <= limit
        
        def push(r):
            nonlocal max_t,min_t
            while max_h<max_t and nums[max_q[max_t-1]]<=nums[r]:
                max_t-=1
            max_q[max_t]=r
            max_t+=1
            while min_h<min_t and nums[min_q[min_t-1]]>=nums[r]:
                min_t-=1
            min_q[min_t]=r
            min_t+=1
        
        def pop(l):
            nonlocal max_h,min_h
            if max_h<max_t and max_q[max_h]==l:
                max_h+=1
            if min_h<min_t and min_q[min_h]==l:
                min_h+=1

        for l in range(n):
            while r<n and ok(limit,nums[r]):
                push(r)
                r+=1
            length=r-l
            ans=length if length>ans else ans 
            pop(l)
        
        return ans