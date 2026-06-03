#测试链接 : https://leetcode.cn/problems/minimum-window-substring/
from collections import defaultdict
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        betbook=defaultdict(int)
        for ch in t :
            betbook[ch]-=1
        conbet=len(t)
        min_len=float('inf')
        sta,l=0,0
        for r,ch in enumerate(s):
            if betbook[ch]<0:
                conbet-=1
            betbook[ch]+=1
            if conbet==0:
                while betbook[s[l]]>0:
                    betbook[s[l]]-=1
                    l+=1
                cur_len=r-l+1
                if cur_len<min_len:
                    min_len=cur_len
                    sta=l
        return '' if min_len==float('inf') else s[sta:sta+min_len]