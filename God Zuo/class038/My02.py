class Solution:
    def subsetsWithDup(self, nums): 
        ans=[]
        nums.sort()
        path=[0]*len(nums)
        def f (i,size):
            if i==len(nums):
                ans.append(path[:size][:])
                return 
            j=i+1
            while  j < len(nums) and nums[j]==nums[i]:
                j+=1
            f(j,size)
            for k in  range(i,j):
               
                path[size]=nums[k]
                size+=1
                f(j,size) 
        f(0,0)
        return list(ans)
        