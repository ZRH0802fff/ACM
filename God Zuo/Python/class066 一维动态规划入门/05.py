# 丑数 II (Ugly Number II)
# 测试链接 : https://leetcode.cn/problems/ugly-number-ii/

def nthUglyNumber(n: int) -> int:
    # dp 数组用于存储前 n 个丑数，索引 1 到 n
    dp = [0] * (n + 1)
    dp[1] = 1
    
    # 初始化三个指针，分别指向乘以 2、3、5 的丑数位置
    i2 = i3 = i5 = 1
    
    for i in range(2, n + 1):
        # 计算下一个可能的丑数
        a = dp[i2] * 2
        b = dp[i3] * 3
        c = dp[i5] * 5
        
        # 找出当前的最小丑数
        cur = min(a, b, c)
        
        # 哪个指针的乘积被选中，对应的指针就向前移动一步
        # 注意这里必须是独立的 if 语句，不能用 elif，
        # 因为可能有重复值（比如 2*3 = 6 和 3*2 = 6），此时两个指针都要移动以去重
        if cur == a:
            i2 += 1
        if cur == b:
            i3 += 1
        if cur == c:
            i5 += 1
            
        dp[i] = cur
        
    return dp[n]

# 测试代码
if __name__ == "__main__":
    test_n = 10
    print(f"第 {test_n} 个丑数是: {nthUglyNumber(test_n)}")