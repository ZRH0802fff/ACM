from typing import List

class Solution:
    def maxArea(self, height: List[int]) -> int:
        ans = 0
        l = 0
        r = len(height) - 1
        
        while l < r:
            # 容器的高度由较短的那块木板决定
            current_height = min(height[l], height[r])
            # 计算当前水量并更新最大值
            ans = max(ans, current_height * (r - l))
            
            # 贪心策略：谁短谁就往里走
            if height[l] <= height[r]:
                l += 1
            else:
                r -= 1
                
        return ans