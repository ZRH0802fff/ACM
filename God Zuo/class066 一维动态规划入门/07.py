# 环绕字符串中唯一的子字符串 (Unique Substrings in Wraparound String)
# 测试链接 : https://leetcode.cn/problems/unique-substrings-in-wraparound-string/

class Solution:
    def findSubstringInWraproundString(self, s: str) -> int:
        if not s:
            return 0
            
        n = len(s)
        # dp[i] 表示以字符 (i + 'a') 结尾的符合要求的子串的最大长度
        dp = [0] * 26
        
        # 初始化第一个字符
        dp[ord(s[0]) - 97] = 1
        length = 1
        
        for i in range(1, n):
            cur_val = ord(s[i])
            pre_val = ord(s[i - 1])
            
            # Pythonic: 利用取模运算完美融合 (当前比前一个大1) 和 (z 到 a 的环绕) 两种情况
            if (cur_val - pre_val) % 26 == 1:
                length += 1
            else:
                length = 1
                
            idx = cur_val - 97 # 97 是 'a' 的 ASCII 码
            dp[idx] = max(dp[idx], length)
            
        # Pythonic: 直接返回列表总和
        return sum(dp)

# 测试代码
if __name__ == "__main__":
    sol = Solution()
    print(f"zab 的结果: {sol.findSubstringInWraproundString('zab')}")
    print(f"cac 的结果: {sol.findSubstringInWraproundString('cac')}")