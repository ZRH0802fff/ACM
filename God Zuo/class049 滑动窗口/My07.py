#测试链接 : https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/
class Solution:
    def longestSubstring(self, s: str, k: int) -> int:
        ans=0
        for require in range(1,27):
            cnts=[0]*128
            l,collect,satisfy=0,0,0
            for r,ch in enumerate(s):
                idx=ord(ch)
                cnts[idx]+=1
                if cnts[idx]==1:
                    collect+=1
                if cnts[idx]==k:
                    satisfy+=1
                while collect>require:
                    lidx=ord(s[l])
                    if cnts[lidx]==1:
                        collect-=1
                    if cnts[lidx]==k:
                        satisfy-=1
                    cnts[lidx]-=1
                    l+=1
                if satisfy==require:
                    ans=max(ans,r-l+1)
        return ans 