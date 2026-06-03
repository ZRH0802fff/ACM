# 测试链接 : https://leetcode.cn/problems/number-of-good-paths/

class Solution:
    def numberOfGoodPaths(self, vals: list[int], edges: list[list[int]]) -> int:
        n = len(vals)
        father=[_ for _ in range(n)]
        maxcnt=[1]*n

        def find(i):
            while  i != father[i]:
                father[i]=father[father[i]]
                i=father[i]
            return i
        
        ans=n
        edges.sort(key=lambda x : max(vals[x[0]],vals[x[1]]))

        for u,v in edges:
            fx=find(u)
            fy=find(v)
            if fx != fy:
                if vals[fx]>vals[fy]:
                    father[fy]=father[fx]
                elif vals[fx]<vals[fy]:
                    father[fx]=father[fy]
                else:
                    ans+=maxcnt[fx]*maxcnt[fy]
                    maxcnt[fx]+=maxcnt[fy]
                    father[fy]=fx
        return ans