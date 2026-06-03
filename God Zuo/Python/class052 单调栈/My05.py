# 测试链接：https://leetcode.cn/problems/maximal-rectangle/
class Solution:
    def maximalRectangle(self, matrix: list[list[str]]) -> int:
        n=len(matrix)
        m=len(matrix[0])
        height=[0]*m
        ans=0
        for i in range(n):
            for j in range(m):
                if matrix[i][j]=='0':
                    height[j]=0
                else:
                    height[j]+=1
            
            stack = []
            for j in range(m):
                while stack and height[stack[-1]] >= height[j]:
                    cur = stack.pop()
                    left = stack[-1] if stack else -1
                    
                    area = height[cur] * (j - left - 1)
                    if area > ans:
                        ans = area
                        
                stack.append(j)

            while stack:
                cur = stack.pop()
                left = stack[-1] if stack else -1
                
                area = height[cur] * (m - left - 1)
                if area > ans:
                    ans = area  
        return ans