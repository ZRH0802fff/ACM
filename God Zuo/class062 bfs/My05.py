# 测试链接 : https://leetcode.cn/problems/trapping-rain-water-ii/\
import heapq
class Solution:
    def trapRainWater(self, heightMap: list[list[int]]) -> int:
        if len(heightMap) < 3 or len(heightMap[0]) < 3:
            return 0
        m,n=len(heightMap),len(heightMap[0])
        visited=[[False]*n for _ in range(m)]
        heap=[]
        for i in range(m):
            for j in range(n):
                if i==0 or i==m-1 or j==0 or j==n-1:
                    heapq.heappush(heap,(heightMap[i][j],i,j))
                    visited[i][j]=True
        ans=0
        move=[-1,0,1,0,-1]
        while heap:
            w,r,c=heapq.heappop(heap)
            ans+=w-heightMap[r][c]
            for i in range(4):
                tr=r+move[i]
                tc=c+move[i+1]
                if 0<=tr<m and 0<=tc<n and not visited[tr][tc]:
                    heapq.heappush(heap,((w if w >heightMap[tr][tc] else heightMap[tr][tc]),tr,tc))
                    visited[tr][tc]=True
        return ans
    