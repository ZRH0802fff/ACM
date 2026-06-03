from typing import List

class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        MOD = 1000000007
        n = len(arr)
        ans = 0
        stack = []
        
        # 遍历阶段
        for i in range(n):
            # 注意：这里必须是 >=，这样才能在处理相同元素时，
            # 保证一侧严格小于，另一侧小于等于，避免重复计算相同范围的子数组
            while stack and arr[stack[-1]] >= arr[i]:
                cur = stack.pop()
                # 弹出时计算 cur 位置作为最小值的辐射范围
                left = stack[-1] if stack else -1
                
                # (cur - left) 是向左辐射的长度，(i - cur) 是向右辐射的长度
                # 组合数原理：左边的情况数 * 右边的情况数
                ans = (ans + (cur - left) * (i - cur) * arr[cur]) % MOD
                
            stack.append(i)  
            
        # 清算阶段
        while stack:
            cur = stack.pop()
            left = stack[-1] if stack else -1
            # 清算阶段意味着右侧没有遇到比它更小的值，所以右边界直接伸展到数组末尾 n
            ans = (ans + (cur - left) * (n - cur) * arr[cur]) % MOD
            
        return ans  