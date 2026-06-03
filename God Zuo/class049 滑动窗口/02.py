class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        # 用字典记录每个字符最后一次出现的索引位置
        # 替代原 Java 代码中的 last[256] 数组
        last_seen = {}
        ans = 0
        l = 0
        
        # 使用 enumerate 同时获取当前字符 char 和 右指针 r
        for r, char in enumerate(s):
            # 如果字符出现过，尝试更新左指针 l
            # 注意：l 只能向右移动，所以要取 max(l, 之前出现的位置 + 1)
            if char in last_seen:
                l = max(l, last_seen[char] + 1)
                
            # 计算当前窗口长度，并更新最大值
            ans = max(ans, r - l + 1)
            
            # 更新当前字符最后一次出现的索引
            last_seen[char] = r
            
        return ans