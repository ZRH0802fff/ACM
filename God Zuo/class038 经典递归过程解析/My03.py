class Solution:
    def permute(self, nums):
        ans=[]
        def f(i):
            if i==len(nums):
                ans.append(nums[:])
                return
            for j in range(1,len(nums)):
                nums[i],nums[j]=nums[j],nums[i]
                f(i+1)
                nums[i],nums[j]=nums[j],nums[i]
            f(0)
            return ans