#测试链接 : https://leetcode.cn/problems/longest-substring-without-repeating-characters/
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        lastidx={}
        ans=0
        l=0
        for r,ch in enumerate(s):
            if ch in lastidx:
                l=max(l,lastidx[ch]+1)
            ans=max(ans,r-l+1)
            lastidx[ch]=r
        return ans 