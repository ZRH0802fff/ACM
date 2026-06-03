class Solution:
    def nthMagicalNumber(self, n: int, a: int, b: int) -> int:
        MOD = 10**9 + 7
        
        # 计算 lcm(a, b) = a * b / gcd(a, b)
        # 先乘再除更安全（虽然 Python int 无溢出，但保持习惯）
        def gcd(x: int, y: int) -> int:
            while y:
                x, y = y, x % y
            return x
        
        lcm_ab = a * b // gcd(a, b) if a and b else 0
        
        # 二分查找：找最小的 m，使得 [1..m] 中能被 a 或 b 整除的数字个数 >= n
        left = 0
        # 右边界可以取 n * max(a,b)，更宽松
        right = n * max(a, b)
        ans = 0
        
        while left <= right:
            mid = left + (right - left) // 2
            # 容斥原理：m//a + m//b - m//lcm
            count = mid // a + mid // b - mid // lcm_ab
            if count >= n:
                ans = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return ans % MOD