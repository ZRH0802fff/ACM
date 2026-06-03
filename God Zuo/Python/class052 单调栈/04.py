class Solution:
    def largestRectangleArea(self, height: list[int]) -> int:
        stack = []  # 原生动态列表充当栈
        ans = 0
        n = len(height)
        
        for i in range(n):
            while stack and height[stack[-1]] >= height[i]:
                cur = stack.pop()
                left = stack[-1] if stack else -1
                
                area = height[cur] * (i - left - 1)
                if area > ans:
                    ans = area
                    
            stack.append(i)
            
        while stack:
            cur = stack.pop()
            left = stack[-1] if stack else -1
            
            area = height[cur] * (n - left - 1)
            if area > ans:
                ans = area
                
        return ans