# 测试链接 : https://leetcode.cn/problems/similar-string-groups/
class Solution:
    def numSimilarGroups(self, strs: list[str]) -> int:
        n=len(strs)
        m=len(strs[0])

        father=list(range(n))
        sets=n

        def find(i):
            if i !=father[i]:
                father[i]=find(father[i])
            return father[i]
        
        def union(x,y):
            nonlocal sets
            fx=find(x)
            fy=find(y)
            if fx != fy:
                father[fx]=fy
                sets-=1

        for i in range(n):
            for j in range(i+1 , n ):
                if find(i)!=find(j):
                    diff=0
                    s1,s2=strs[i],strs[j]
                    for k in range(m):
                        if s1[k]!=s2[k]:
                            diff+=1
                            if diff >2:
                                break
                    if diff==0 or diff==2:
                        union(i,j)
        return sets   