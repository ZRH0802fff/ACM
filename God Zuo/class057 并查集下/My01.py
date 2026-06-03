# 测试链接 : https://leetcode.cn/problems/most-stones-removed-with-same-row-or-column/
class Solution:
    def removeStones(self, stones: list[list[int]]) -> int:
        n=len(stones)
        father=[i for i in range(n)]
        sets=n

        def find(i):
            if i!=father[i]:
                father[i]=find(father[i])
            return father[i]
        
        def union(x,y):
            nonlocal sets
            fx=find(x)
            fy=find(y)
            if fx != fy:
                father[fx]=fy
                sets-=1
        
        row_first={}
        col_first={}
        for i in range(n):
            row,col=stones[i]
            if row not in row_first:
                row_first[row]=i
            else:
                union(i,row_first[row])
            if col not in col_first:
                col_first[col]=i
            else:
                union(i,col_first[col])
        
        return n-sets