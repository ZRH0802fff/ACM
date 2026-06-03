# 测试链接 : https://leetcode.cn/problems/sum-of-subarray-minimums/
from typing import List

class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        MOD = 1000000007
        n=len(arr)
        stack=[]
        ans=0

        for i in range(n):
            while stack and arr[i]<=arr[stack[-1]]:
                cur=stack.pop()
                left=stack[-1] if stack else -1
                ans=(ans+(cur - left) * (i - cur) * arr[cur])%MOD
            stack.append(i)

        while stack:
            cur=stack.pop()
            left=stack[-1] if stack else -1
            ans = (ans + (cur - left) * (n - cur) * arr[cur]) % MOD
        
        return ans