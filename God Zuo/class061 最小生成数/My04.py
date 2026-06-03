#测试链接 : https://leetcode.cn/problems/checking-existence-of-edge-length-limited-paths/
class Solution:
    def distanceLimitedPathsExist(self, n: int, edges: list[list[int]], queries: list[list[int]]) -> list[bool]:
        edges.sort(key=lambda x :x[2])
        questions=[(q[0],q[1],q[2],i) for i,q in enumerate(queries)]
        questions.sort(key=lambda x : x[2])
        father=[i for i in range(n)]

        def find(i):
            while i != father[i]:
                father[i] = father[father[i]]
                i=father[i] 
            return i 
        
        m=len(edges)
        ans=[False]*len(queries)
        j=0

        for p,q,limit,idx in questions:
            while j<m and edges[j][2]<limit :
                fu=find(edges[j][0])
                fv=find(edges[j][1])
                if fu != fv:
                    father[fu]=fv
                j+=1
            ans[idx]=True if find(p)==find(q) else False
        
        return ans