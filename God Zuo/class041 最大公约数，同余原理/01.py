class Code01_GcdAndLcm:
    
    @staticmethod
    def gcd(a: int, b: int) -> int:
        """
        最大公约数（辗转相除法 / 欧几里得算法）
        证明：gcd(a, b) = gcd(b, a % b)
        """
        return a if b == 0 else Code01_GcdAndLcm.gcd(b, a % b)

    @staticmethod
    def lcm(a: int, b: int) -> int:
        """
        最小公倍数 = |a * b| / gcd(a, b)
        使用 a // gcd * b 避免溢出（但 Python int 无溢出问题）
        """
        if a == 0 or b == 0:
            return 0
        return abs(a) // Code01_GcdAndLcm.gcd(abs(a), abs(b)) * abs(b)


# 测试
if __name__ == "__main__":
    print(Code01_GcdAndLcm.gcd(48, 18))    # 6
    print(Code01_GcdAndLcm.lcm(48, 18))    # 144
    print(Code01_GcdAndLcm.gcd(7, 13))     # 1
    print(Code01_GcdAndLcm.lcm(7, 13))     # 91
    print(Code01_GcdAndLcm.gcd(100, 0))    # 100
    print(Code01_GcdAndLcm.lcm(100, 0))    # 0