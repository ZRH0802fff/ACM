# 解码方法 II (Decode Ways II)
# 测试链接 : https://leetcode.cn/problems/decode-ways-ii/

MOD = 10**9 + 7

# ==========================================
# 1. 暴力尝试 (无取模逻辑，纯递归)
# ==========================================
def numDecodings1(s: str) -> int:
    n = len(s)
    
    # s[i....] 有多少种有效转化
    def f1(i: int) -> int:
        if i == n:
            return 1
        if s[i] == '0':
            return 0
            
        # 1) i 想单独转
        ans = f1(i + 1) * (9 if s[i] == '*' else 1)
        
        # 2) i 和 i+1 一起转化 (需要 <= 26)
        if i + 1 < n:
            if s[i] != '*':
                if s[i + 1] != '*':
                    # num num (利用 Python 切片直接转数字判断)
                    if int(s[i:i+2]) <= 26:
                        ans += f1(i + 2)
                else:
                    # num *
                    if s[i] == '1':
                        ans += f1(i + 2) * 9
                    elif s[i] == '2':
                        ans += f1(i + 2) * 6
            else:
                if s[i + 1] != '*':
                    # * num
                    if s[i + 1] <= '6':
                        ans += f1(i + 2) * 2
                    else:
                        ans += f1(i + 2)
                else:
                    # * * (11~19, 21~26 共 15 种可能)
                    ans += f1(i + 2) * 15
                    
        return ans
        
    return f1(0)


# ==========================================
# 2. 记忆化搜索 (带有取模逻辑)
# ==========================================
def numDecodings2(s: str) -> int:
    n = len(s)
    dp = [-1] * n
    
    def f2(i: int) -> int:
        if i == n:
            return 1
        if s[i] == '0':
            return 0
        if dp[i] != -1:
            return dp[i]
            
        ans = f2(i + 1) * (9 if s[i] == '*' else 1)
        
        if i + 1 < n:
            if s[i] != '*':
                if s[i + 1] != '*':
                    if int(s[i:i+2]) <= 26:
                        ans += f2(i + 2)
                else:
                    if s[i] == '1':
                        ans += f2(i + 2) * 9
                    elif s[i] == '2':
                        ans += f2(i + 2) * 6
            else:
                if s[i + 1] != '*':
                    if s[i + 1] <= '6':
                        ans += f2(i + 2) * 2
                    else:
                        ans += f2(i + 2)
                else:
                    ans += f2(i + 2) * 15
                    
        ans %= MOD
        dp[i] = ans
        return ans
        
    return f2(0)


# ==========================================
# 3. 严格位置依赖的动态规划 (自底向上)
# ==========================================
def numDecodings3(s: str) -> int:
    n = len(s)
    dp = [0] * (n + 1)
    dp[n] = 1
    
    for i in range(n - 1, -1, -1):
        if s[i] != '0':
            dp[i] = (9 if s[i] == '*' else 1) * dp[i + 1]
            
            if i + 1 < n:
                if s[i] != '*':
                    if s[i + 1] != '*':
                        if int(s[i:i+2]) <= 26:
                            dp[i] += dp[i + 2]
                    else:
                        if s[i] == '1':
                            dp[i] += dp[i + 2] * 9
                        elif s[i] == '2':
                            dp[i] += dp[i + 2] * 6
                else:
                    if s[i + 1] != '*':
                        if s[i + 1] <= '6':
                            dp[i] += dp[i + 2] * 2
                        else:
                            dp[i] += dp[i + 2]
                    else:
                        dp[i] += dp[i + 2] * 15
                        
            dp[i] %= MOD
            
    return dp[0]


# ==========================================
# 4. 空间优化的动态规划 (推荐)
# ==========================================
def numDecodings4(s: str) -> int:
    n = len(s)
    nxt = 1      # 对应 dp[i+1]
    nxt_nxt = 0  # 对应 dp[i+2]
    
    for i in range(n - 1, -1, -1):
        if s[i] == '0':
            cur = 0
        else:
            cur = (9 if s[i] == '*' else 1) * nxt
            
            if i + 1 < n:
                if s[i] != '*':
                    if s[i + 1] != '*':
                        if int(s[i:i+2]) <= 26:
                            cur += nxt_nxt
                    else:
                        if s[i] == '1':
                            cur += nxt_nxt * 9
                        elif s[i] == '2':
                            cur += nxt_nxt * 6
                else:
                    if s[i + 1] != '*':
                        if s[i + 1] <= '6':
                            cur += nxt_nxt * 2
                        else:
                            cur += nxt_nxt
                    else:
                        cur += nxt_nxt * 15
                        
            cur %= MOD
            
        # 滚动更新变量
        nxt_nxt, nxt = nxt, cur
        
    return nxt

# 测试代码
if __name__ == "__main__":
    test_str = "1*"
    print(f"numDecodings1: {numDecodings1(test_str)}")
    print(f"numDecodings2: {numDecodings2(test_str)}")
    print(f"numDecodings3: {numDecodings3(test_str)}")
    print(f"numDecodings4: {numDecodings4(test_str)}")