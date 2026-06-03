class Solution:
    def minCostToSupplyWater(self, n: int, wells: list[int], pipes: list[list[int]]) -> int:
        edges=[]
        for i in range(n):
            edges.append((0,i+1,wells[i]))
        for u,v,w in pipes:
            edges.append((u,v,w))
        
        father=[i for i in range(n+1)]
        edges.sort(key=lambda x : x[2])

        def find(i):
            while i !=father[i]:
                father[i]=father[father[i]]
                i=father[i] 
            return i
        
        ans=0
        ed_count=0

        for u,v,w in edges:
            fx=find(u)
            fy=find(v)
            if fx != fy:
                father[fx]=fy
                ans +=w 
                ed_count+=1
                if ed_count==n:
                    break
        return ans