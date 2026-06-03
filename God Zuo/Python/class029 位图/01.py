import random
from typing import List

# 位图的实现
# Bitset(int size)
# void add(int num)
# void remove(int num)
# void reverse(int num)
# boolean contains(int num)
class Bitset:
    def __init__(self, n: int):
        # n个数字 : 0~n-1
        # a/b如果结果想向上取整，可以写成 : (a + b - 1) // b
        # 前提是a和b都是非负数
        self.set: List[int] = [0] * ((n + 31) // 32)

    def add(self, num: int) -> None:
        self.set[num // 32] |= 1 << (num % 32)

    def remove(self, num: int) -> None:
        self.set[num // 32] &= ~(1 << (num %  32))

    def reverse(self, num: int) -> None:
        self.set[num // 32] ^= 1 << (num % 32)

    def contains(self, num: int) -> bool: 
        return ((self.set[num // 32] >> (num % 32)) & 1) == 1

# 对数器测试
if __name__ == "__main__":
    n = 1000
    test_times = 10000
    print("测试开始")
    # 实现的位图结构
    bit_set = Bitset(n)
    # 直接用set做对比测试
    hash_set = set()
    print("调用阶段开始")
    for i in range(test_times):
        decide = random.random()
        # number -> 0 ~ n-1，等概率得到
        number = int(random.random() * n)
        if decide < 0.333:
            bit_set.add(number)
            hash_set.add(number)
        elif decide < 0.666:
            bit_set.remove(number)
            if number in hash_set:
                hash_set.remove(number)
        else:
            bit_set.reverse(number)
            if number in hash_set:
                hash_set.remove(number)
            else:
                hash_set.add(number)
    print("调用阶段结束")
    print("验证阶段开始")
    for i in range(n):
        if bit_set.contains(i) != (i in hash_set):
            print("出错了!")
    print("验证阶段结束")
    print("测试结束")