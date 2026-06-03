class Solution:
    def maximalRectangle(self, matrix: list[list[str]]) -> int:
        if not matrix or not matrix[0]:
            return 0
            
        n = len(matrix)
        m = len(matrix[0])
        
        # 对应 Java 版的 int[] height = new int[MAXN];
        # 初始化一次，后续原地修改，速度极快
        height = [0] * m 
        ans = 0
        
        for i in range(n):
            # 1. 数组压缩：来到第 i 行，加工出以 i 行为底的直方图高度
            for j in range(m):
                if matrix[i][j] == '0':
                    height[j] = 0
                else:
                    height[j] += 1
            
            # 2. 内联单调栈逻辑：计算当前直方图的最大矩形面积
            # 不额外封装为方法，直接省去高频的函数调用开销
            stack = []
            for j in range(m):
                while stack and height[stack[-1]] >= height[j]:
                    cur = stack.pop()
                    left = stack[-1] if stack else -1
                    
                    area = height[cur] * (j - left - 1)
                    if area > ans:
                        ans = area
                        
                stack.append(j)
                
            # 清算留在栈中的元素
            while stack:
                cur = stack.pop()
                left = stack[-1] if stack else -1
                
                area = height[cur] * (m - left - 1)
                if area > ans:
                    ans = area
                    
        return ans