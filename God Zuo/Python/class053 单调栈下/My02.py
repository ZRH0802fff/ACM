# 测试链接 : https://leetcode.cn/problems/remove-duplicate-letters/
from collections import Counter

class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        cnts=Counter(s)
        book=set()
        stack=[]
        for cur in s:
            cnts[cur]-=1
            if cur not in book:
                while stack and cur<stack[-1] and cnts[stack[-1]]>0:
                    book.remove(stack.pop())
                stack.append(cur)    
                book.add(cur)
        return "".join(stack)