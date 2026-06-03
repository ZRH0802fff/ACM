def f1(a: int, b: int, c: int, d: int, mod: int) -> int:
    """
    使用大整数逐行计算，不依赖取模技巧（模拟 BigInteger）
    """
    # Python int 本身支持任意大整数，所以可以直接计算
    o1 = a
    o2 = b
    o3 = c
    o4 = d
    o5 = o1 + o2
    o6 = o3 - o4
    o7 = o1 * o3
    o8 = o2 * o4
    o9 = o5 * o6
    o10 = o7 - o8
    o11 = o9 + o10
    # 取模并保证非负
    result = o11 % mod
    return result if result >= 0 else result + mod


def f2(a: int, b: int, c: int, d: int, mod: int) -> int:
    """
    使用同余原理，边计算边取模（推荐实际使用）
    """
    o1 = a % mod
    o2 = b % mod
    o3 = c % mod
    o4 = d % mod
    
    o5 = (o1 + o2) % mod
    o6 = (o3 - o4 + mod) % mod
    o7 = (o1 * o3) % mod
    o8 = (o2 * o4) % mod
    o9 = (o5 * o6) % mod
    o10 = (o7 - o8 + mod) % mod
    ans = (o9 + o10) % mod
    return ans


import random

def random_long():
    """模拟 Java 的 random()，返回 [0, 2^63-1) 的随机 long"""
    return random.randint(0, (1 << 63) - 1)


if __name__ == "__main__":
    print("测试开始")
    test_time = 100000
    mod = 1000000007
    
    for _ in range(test_time):
        a = random_long()
        b = random_long()
        c = random_long()
        d = random_long()
        if f1(a, b, c, d, mod) != f2(a, b, c, d, mod):
            print("出错了!")
            break
    else:
        print("测试结束，全部正确")

    print("===")
    a = random_long()
    b = random_long()
    c = random_long()
    d = random_long()
    print(f"a : {a}")
    print(f"b : {b}")
    print(f"c : {c}")
    print(f"d : {d}")
    print("===")
    print(f"f1 : {f1(a, b, c, d, mod)}")
    print(f"f2 : {f2(a, b, c, d, mod)}")