from collections import defaultdict

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        # 使用 defaultdict(int) 记录每种字符的欠债情况
        # 默认值为 0，负数代表有负债，正数代表有盈余
        cnts = defaultdict(int)
        for char in t:
            cnts[char] -= 1
            
        min_len = float('inf')
        start = 0
        debt = len(t)
        l = 0
        
        # 使用 enumerate 同时获取右指针 r 和当前字符 char
        for r, char in enumerate(s):
            # 窗口右边界向右，拿到字符，偿还债务
            # 注意：Python 没有 cnts[char]++ 这种写法，所以先判断再加 1
            if cnts[char] < 0:
                debt -= 1
            cnts[char] += 1
            
            # 当债务清零，说明当前窗口已经包含了 t 中的所有字符
            if debt == 0:
                # 窗口左边界尝试向右收缩，把盈余的多余字符吐出来
                while cnts[s[l]] > 0:
                    cnts[s[l]] -= 1
                    l += 1
                
                # 更新最小覆盖子串的起始位置和长度
                current_len = r - l + 1
                if current_len < min_len:
                    min_len = current_len
                    start = l
                    
        return "" if min_len == float('inf') else s[start : start + min_len]