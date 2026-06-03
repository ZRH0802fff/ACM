#测试链接：https://leetcode.cn/problems/largest-rectangle-in-histogram
class Solution:
    def largestRectangleArea(self, height: list[int]) -> int:
        stack=[]
        ans=0
        n=len(height)
        for i in range(n):
            while stack and height[i]<=height[stack[-1]]:
                cur=stack.pop()
                left=stack[-1] if stack else -1
                area=height[cur]*(i-left-1)
                ans=max(ans,area)
            stack.append(i)
        while stack:
            cur=stack.pop()
            left=stack[-1] if stack else -1
            area=height[cur] *(n-left-1)
            ans=max(ans , area)
        return ans