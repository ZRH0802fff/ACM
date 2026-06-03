class Solution:
    def minSubarray(self, nums, p):
        mod,sum=0
        for num in nums:
            sum+=num
        mod=sum%p
        if mod==0:
            return 0
        ans=float('inf')
        cur=0
        book={0:-1}
        for i in range(nums):
            cur=(cur+nums[i])%p
            find=(cur-mod+p)%p
            if find in book:
                ans=min(ans,i-book[find])
            book[cur]=i
        return -1 if ans==len(nums) else ans
    