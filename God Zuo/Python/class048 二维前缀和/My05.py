#测试链接 : https://leetcode.cn/problems/xepqZ5/
from typing import List

class Solution:
    def fieldOfGreatestBlessing(self, fields: List[List[int]]) -> int:
        xset=set()
        yset=set()
        for x , y , r in fields:
            xset.add((x<<1)-r)
            xset.add((x<<1)+r)
            yset.add((y<<1)-r)
            yset.add((y<<1)+r)
        x_idx={val:i for i , val in enumerate(sorted(xset),1)}
        y_idx={val:i for i , val in enumerate(sorted(yset),1)}
        xsize=len(x_idx)
        ysize=len(y_idx)
        diff=[[0]*(ysize+2) for _ in range(xsize+2)]
        for x,y,r in fields:
            a=x_idx[(x<<1)-r]
            c=x_idx[(x<<1)+r]
            b=y_idx[(y<<1)-r]
            d=y_idx[(y<<1)+r]
            diff[a][b]+=1
            diff[c+1][d+1]+=1
            diff[c+1][b]-=1
            diff[a][d+1]-=1
        ans=0
        for i in range (1,xsize+1):
            for j in range(1,ysize+1):
                diff[i][j]+=diff[i-1][j]+diff[i][j-1]-diff[i-1][j-1]
                if diff[i][j]>ans:
                    ans=diff[i][j]
        return ans 