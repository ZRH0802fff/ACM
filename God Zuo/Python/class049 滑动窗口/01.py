from typing import List

class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        # 使用 float('inf') 代表无穷大，等同于 Java 的 Integer.MAX_VALUE
        ans = float('inf')
        l = 0
        window_sum = 0
        
        for r in range(len(nums)):
            window_sum += nums[r]
            
            # 只要把左边界 l 位置的数从窗口移出后，和仍然 >= target
            # 就果断移出，以此来缩短子数组的长度
            while window_sum - nums[l] >= target:
                window_sum -= nums[l]
                l += 1
                
            # 记录满足条件的最小长度
            if window_sum >= target:
                ans = min(ans, r - l + 1)
                
        # 如果 ans 还是无穷大，说明没有找到符合条件的子数组，返回 0
        return 0 if ans == float('inf') else ans