# 测试链接 : https://leetcode.cn/problems/couples-holding-hands/
class Solution:
    def minSwapsCouples(self, row: list[int]) -> int:
        n=len(row)
        cp=n//2
        father=[_ for _ in range(n+1)]
        sets=cp
        
        def find(i):
            if i !=father[i]:
                father[i]=find(father[i])
            return father[i]
        
        def union(x,y):
            nonlocal sets
            tx=find(x)
            ty=find(y)
            if tx != ty:
                father[tx]=find(ty)
                sets-=1
        
        for i in range(0,n,2):
            union(row[i]//2,row[i+1]//2)
        return cp-sets