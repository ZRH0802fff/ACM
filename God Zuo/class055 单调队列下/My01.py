# 测试链接 : https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/
class Solution:
    def shortestSubarray(self, nums: list[int], k: int) -> int:
        n=len(nums)
        pref=[0]*(n+1)
        for i in range(n):
            pref[i+1]=pref[i]+nums[i]
        q=[0]*(n+1)
        h=t=0
        ans=float('inf')
        for r in range(n+1):
            while h<t and pref[r]-pref[q[h]]>=k:
                length=r-q[h]
                if length<ans:
                    ans=length
                h+=1
            while h<t and pref[q[t-1]]>=pref[r]:
                t-=1
            q[t]=r
            t+=1
        return ans if ans!=float('inf') else -1