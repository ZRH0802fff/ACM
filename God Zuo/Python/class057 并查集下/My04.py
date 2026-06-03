# 测试链接 : https://leetcode.cn/problems/minimize-malware-spread-ii/
class Solution:
    def minMalwareSpread(self, graph: list[list[int]], initial: list[int]) -> int:
        n = len(graph)
        initial_set=set(initial)
        father=list(range(n))
        size=[1]*n

        def find(i):
            while i != father[i]:
                father[i]=father[father[i]]
                i=father[i] 
            return i
        
        def union(x,y):
            fx=find(x)
            fy=find(y)
            if fx != fy:
                father[fx]=fy
                size[fy]+=size[fx]
        
        for i in range(n):
            if i in initial_set:
                continue
            for j in range(i+1,n):
                if j not in initial_set and graph[i][j]==1:
                    union(i,j)
        
        infect=[-1]*n
        for sick in initial:
            for ng in range(n):
                if ng not in initial_set and graph[sick][ng]==1:
                    fn=find(ng)
                    if infect[fn]==-1:
                        infect[fn]=sick
                    elif infect[fn]!= -2 and infect[fn] !=sick:
                        infect[fn]=-2

        cnts=[0]*n
        for i in range(n):
            if i==father[i] and infect[i]>=0:
                cnts[infect[i]]+=size[i]
        initial.sort()
        ans=initial[0]
        max_saved=cnts[ans]
        for i in initial:
            if cnts[i]>max_saved:
                ans=i
                max_saved=cnts[i] 
        return ans 