# 测试链接 : https://leetcode.cn/problems/stickers-to-spell-word/
class Solution:
    def minStickers(self, stickers: list[str], target: str) -> int:
        graph=[[]for _ in range(26) ]
        for str in stickers:
            s=''.join(sorted(str))
            for i in range(len(s)):
                if i==0 or s[i]!=s[i-1]:
                    graph[ord(s[i])-ord('a')].append(s)
        
        target=''.join(sorted(target))
        visited=set([target])
        queue=[target]
        l,r,level=0,1,1

        def getnxt(t,s):
            res=[]
            i,j=0,0
            while i<len(t):
                if j==len(s):
                    res.append(t[i])
                    i+=1
                elif t[i]<s[j]:
                    res.append(t[i])
                    i+=1
                elif t[i]>s[j]:
                    j+=1
                else:
                    i+=1
                    j+=1
            return ''.join(res)
        
        while l<r:
            size=r-l
            for _ in range(size):
                cur=queue[l]
                l+=1
                frid=ord(cur[0])-ord('a')
                for s in graph[frid]:
                    nxt=getnxt(cur,s)
                    if not nxt:
                        return level
                    elif nxt not in visited:
                        visited.add(nxt)
                        queue.append(nxt)
                        r+=1
            level+=1
        return -1
