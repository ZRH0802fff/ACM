# 测试链接 : https://leetcode.cn/problems/max-value-of-equation/
class Solution:
    def findMaxValueOfEquation(self, points: list[list[int]], k: int) -> int:
        n=len(points)
        q=[(0,0)]*n
        h=t=0
        ans=-float('inf')
        for x,y in points:
            while h<t and x-q[h][0]>k:
                h+=1
            if h<t:
                cur=x+y+q[h][1]
                if cur>ans:
                    ans=cur
            diff=y-x
            while h<t and q[t-1][1]<=diff:
                t-=1
            q[t]=(x,diff)
            t+=1
        return ans