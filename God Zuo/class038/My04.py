class Solution:
    def permuteUnique(self, nums):
        ans=[]
        def f (i):
            if i==len(nums):
                ans.append(nums[:])
                return 
            book=set()
            for j in range(i,len(nums)):
                if nums[j] in book:
                    continue
                book.add(nums[j])
                nums[i],nums[j]=nums[j],nums[i]
                f(i+1)
                nums[i],nums[j]=nums[j],nums[i]
        f(0)
        return ans
