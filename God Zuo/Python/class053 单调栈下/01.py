class Solution:
    def maxWidthRamp(self, nums: list[int]) -> int:
        # stack 初始化放入 0，对应 Java 中的 r = 1, stack[0] = 0
        stack = [0]
        n = len(nums)
        
        # 1. 从左往右，建立严格单调递减栈（存的是索引）
        for i in range(1, n):
            if nums[stack[-1]] > nums[i]:
                stack.append(i)
                
        ans = 0
        
        # 2. 从右往左，寻找最大宽度坡
        for j in range(n - 1, -1, -1):
            # 当栈不为空，且栈顶索引对应的值 <= 当前 j 的值时，说明找到了坡
            while stack and nums[stack[-1]] <= nums[j]:
                i = stack.pop()
                width = j - i
                
                # 竞赛常数优化：使用 if 替代 ans = max(ans, width)
                if width > ans:
                    ans = width
                    
        return ans