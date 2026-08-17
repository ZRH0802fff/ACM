class Solution:
    def longestWPI(self, hours) :
        book={0:-1}
        ans,sum=0,0
        for i in range(len(hours)):
            sum+=1 if hours[i]>8 else -1
            if sum>0:
                ans=i+1
            else:
                if sum-1 in book:
                    ans=max(ans,i-book[sum-1])
            if sum not in book:
                book[sum]=i
        return ans