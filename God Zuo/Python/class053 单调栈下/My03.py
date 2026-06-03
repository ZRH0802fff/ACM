class Solution:
    def totalSteps(self, nums: list[int]) -> int:
        ans=0
        stack=[]
        for i in range (len(nums)-1,-1,-1):
            cur_t=0
            while stack and nums[i]>stack[-1][0]:
                pre_w,pre_t=stack.pop()
                cur_t+=1
                if pre_t>cur_t:
                    cur_t=pre_t
            stack.append((nums[i],cur_t))
            if cur_t > ans:
                ans = cur_t
        return ans