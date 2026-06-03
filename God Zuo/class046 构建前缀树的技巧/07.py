from typing import List

class Solution:
    def findTheLongestSubstring(self, s: str) -> int:
        n = len(s)
        # 状态数组：32 种状态（5个元音的奇偶性用5位二进制表示）
        # -2 表示该状态从未出现过
        state = [-2] * 32
        state[0] = -1  # 空字符串的状态最早出现在 -1
        
        ans = 0
        status = 0     # 当前前缀的元音奇偶性状态
        
        for i in range(n):
            cha = s[i]
            # 将当前字符映射为位位置（a=0, e=1, i=2, o=3, u=4）
            m = -1
            if cha == 'a':
                m = 0
            elif cha == 'e':
                m = 1
            elif cha == 'i':
                m = 2
            elif cha == 'o':
                m = 3
            elif cha == 'u':
                m = 4
            
            # 如果是元音，翻转对应位的奇偶性
            if m != -1:
                status ^= (1 << m)
            
            # 如果该状态之前出现过，更新最长长度
            if state[status] != -2:
                ans = max(ans, i - state[status])
            else:
                # 第一次出现该状态，记录最早位置
                state[status] = i
        
        return ans


# ==================== 测试示例 ====================
if __name__ == "__main__":
    solution = Solution()
    
    # 示例 1
    print(solution.findTheLongestSubstring("eleetminicoworoep"))  # 输出: 13
    
    # 示例 2
    print(solution.findTheLongestSubstring("leetcode"))           # 输出: 5
    
    # 示例 3
    print(solution.findTheLongestSubstring("bcbcbc"))            # 输出: 6