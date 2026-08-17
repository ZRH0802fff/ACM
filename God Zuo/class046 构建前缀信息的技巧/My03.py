def subarraySum(nums, aim) :
    book={0:1}
    ans,sum=0,0
    for num in nums :
        sum+=num
        ans=book.get(sum-aim,0)
        book[sum]=book.get(sum,0)+1
    return ans