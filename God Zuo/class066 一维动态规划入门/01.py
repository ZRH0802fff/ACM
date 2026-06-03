from functools import cache

# ==========================================
# 斐波那契数列计算的四种递进实现
# ==========================================

# 1. 暴力递归 (时间复杂度 O(2^n)，空间复杂度 O(n))
def fib1(n: int) -> int:
    def f1(i: int) -> int:
        if i < 2:
            return i
        return f1(i - 1) + f1(i - 2)
    
    return f1(n)

def fib2(n: int) -> int:
    # 初始化 dp 数组，长度为 n+1，初始值设为 -1 表示未计算过
    dp = [-1] * (n + 1)
    
    def f2(i: int) -> int:
        if i < 2:
            return i
            
        # 如果 dp[i] 不为 -1，说明之前已经计算过了，直接拿来用（剪枝）
        if dp[i] != -1:
            return dp[i]
            
        # 如果没计算过，就进行递归计算
        ans = f2(i - 1) + f2(i - 2)
        
        # 将计算结果记录在 dp 数组中，方便下次直接使用
        dp[i] = ans
        return ans
    
    return f2(n)

# 3. 动态规划 (时间复杂度 O(n)，空间复杂度 O(n))
# 严格按照自底向上的顺序填表
def fib3(n: int) -> int:
    if n < 2:
        return n
    
    dp = [0] * (n + 1)
    dp[1] = 1
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
        
    return dp[n]

# 4. 空间优化的动态规划 (时间复杂度 O(n)，空间复杂度 O(1))
# 使用 Python 的元组解构特性，省略中间变量 cur，写法最精简
def fib4(n: int) -> int:
    if n < 2:
        return n
    
    last_last, last = 0, 1
    for _ in range(2, n + 1):
        last_last, last = last, last_last + last
        
    return last

# 测试代码
if __name__ == "__main__":
    test_n = 10
    print(f"fib1({test_n}) = {fib1(test_n)}")
    print(f"fib2({test_n}) = {fib2(test_n)}")
    print(f"fib3({test_n}) = {fib3(test_n)}")
    print(f"fib4({test_n}) = {fib4(test_n)}")