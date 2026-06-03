# 解码方法 (Decode Ways)
# 测试链接 : https://leetcode.cn/problems/decode-ways/

# ==========================================
# 1. 暴力尝试 (纯递归)
# ==========================================
def numDecodings1(s: str) -> int:
    n = len(s)
    
    # s[i....] 有多少种有效的转化方案
    def f1(i: int) -> int:
        if i == n:
            return 1
            
        if s[i] == '0':
            return 0
            
        ans = f1(i + 1)
        # Pythonic: 利用切片直接取两位字符并转为整数判断
        if i + 1 < n and int(s[i:i+2]) <= 26:
            ans += f1(i + 2)
            
        return ans
        
    return f1(0)


# ==========================================
# 2. 暴力尝试改记忆化搜索 (手动维护 dp 数组)
# ==========================================
def numDecodings2(s: str) -> int:
    n = len(s)
    dp = [-1] * n
    
    def f2(i: int) -> int:
        if i == n:
            return 1
        if dp[i] != -1:
            return dp[i]
            
        if s[i] == '0':
            ans = 0
        else:
            ans = f2(i + 1)
            if i + 1 < n and int(s[i:i+2]) <= 26:
                ans += f2(i + 2)
                
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
    
    # 从后往前填表
    for i in range(n - 1, -1, -1):
        if s[i] == '0':
            dp[i] = 0
        else:
            dp[i] = dp[i + 1]
            if i + 1 < n and int(s[i:i+2]) <= 26:
                dp[i] += dp[i + 2]
                
    return dp[0]


# ==========================================
# 4. 严格位置依赖的动态规划 + 空间压缩 (推荐)
# ==========================================
def numDecodings4(s: str) -> int:
    n = len(s)
    nxt = 1      # 对应 dp[i+1]
    nxt_nxt = 0  # 对应 dp[i+2]
    
    for i in range(n - 1, -1, -1):
        if s[i] == '0':
            cur = 0
        else:
            cur = nxt
            if i + 1 < n and int(s[i:i+2]) <= 26:
                cur += nxt_nxt
                
        # Pythonic: 利用元组解构同时更新状态，无需额外临时变量
        nxt_nxt, nxt = nxt, cur
        
    return nxt

# 测试代码
if __name__ == "__main__":
    test_str = "11106"
    print(f"numDecodings1: {numDecodings1(test_str)}")
    print(f"numDecodings2: {numDecodings2(test_str)}")
    print(f"numDecodings3: {numDecodings3(test_str)}")
    print(f"numDecodings4: {numDecodings4(test_str)}")