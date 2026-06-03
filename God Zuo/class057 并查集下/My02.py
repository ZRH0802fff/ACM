# 链接测试 : https://leetcode.cn/problems/find-all-people-with-secret/
class Solution:
    def findAllPeople(self, n: int, meetings: list[list[int]], firstPerson: int) -> list[int]:
        father=[_ for _ in range(n)]
        secret=[False]*n
        father[firstPerson]=0
        secret[0]=True

        def find(i):
            if i !=father[i]:
                father[i]=find(father[i])
            return father[i]
        
        def union(x,y):
            fx=find(x)
            fy=find(y)
            if fx != fy:
                father[fx]=fy
                secret[fy]|=secret[fx]
        
        m=len(meetings)
        l=0
        meetings.sort(key= lambda x :x[2])
        while l<m:
            r=l
            while r+1<m and meetings[l][2]==meetings[r+1][2]:
                r+=1
            for i in range(l,r+1):
                union(meetings[i][0],meetings[i][1])
            for i in range(l,r+1):
                a,b,_=meetings[i]
                if  not secret[find(a)]:
                    father[a]=a
                    father[b]=b
            l=r+1
        ans=[]
        for i in range(n):
            if secret[find(i)]:
                ans.append(i)
        
        return ans