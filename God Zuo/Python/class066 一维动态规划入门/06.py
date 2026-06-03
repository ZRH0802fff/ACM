# 最长有效括号 (Longest Valid Parentheses)
# 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/

class Solution:
    def longestValidParentheses(self, s: str) -> int:
        if not s:
            return 0
            
        n = len(s)
        # dp[i] : 子串必须以 i 位置的字符结尾的情况下，往左整体有效的最大长度
        dp = [0] * n
        ans = 0
        
        for i in range(1, n):
            if s[i] == ')':
                # p 是可能与当前 ')' 匹配的 '(' 的位置
                # 即当前位置 i 减去它前面已经配对成功的括号长度，再往前看一个字符
                p = i - dp[i - 1] - 1
                
                if p >= 0 and s[p] == '(':
                    # 如果配对成功，当前长度 = 前面已成对的长度 + 2 (这一对) + p 之前已成对的长度
                    dp[i] = dp[i - 1] + 2 + (dp[p - 1] if p - 1 >= 0 else 0)
                    
            # 记录遍历过程中的最大值
            ans = max(ans, dp[i])
            
        return ans

# 测试代码
if __name__ == "__main__":
    test_str = ")()())"
    sol = Solution()
    print(f"最长有效括号长度: {sol.longestValidParentheses(test_str)}")