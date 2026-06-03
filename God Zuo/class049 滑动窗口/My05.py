#测试链接 : https://leetcode.cn/problems/replace-the-substring-for-balanced-string/
from collections import Counter

class Solution:
    def balancedString(self, s: str) -> int:
        n=len(s)
        xu_num=n//4
        counts=Counter(s)
        betbook={}
        conbet=0
        for ch in "QWER":
            if counts[ch]>xu_num:
                betbook[ch]=xu_num-counts[ch]
                conbet-=betbook[ch]
            else:
                betbook[ch]=0
        if conbet==0:
            return 0
        ans=float('inf')
        l=0
        for r,ch in enumerate(s):
            if betbook[ch]<0:
                conbet-=1
            betbook[ch]+=1
            if conbet==0:
                while betbook[s[l]]>0:
                    betbook[s[l]]-=1
                    l+=1
                ans=min(ans,r-l+1)
        return ans