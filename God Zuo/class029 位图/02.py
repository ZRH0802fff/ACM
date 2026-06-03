# 位图的实现
# Bitset是一种能以紧凑形式存储位的数据结构
# Bitset(int n) : 初始化n个位，所有位都是0
# void fix(int i) : 将下标i的位上的值更新为1
# void unfix(int i) : 将下标i的位上的值更新为0
# void flip() : 翻转所有位的值
# boolean all() : 是否所有位都是1
# boolean one() : 是否至少有一位是1
# int count() : 返回所有位中1的数量
# String toString() : 返回所有位的状态
class Bitset:
    def __init__(self, n: int):
        self.set = [0] * ((n + 31) // 32)
        self.size = n
        self.zeros = n
        self.ones = 0
        self.reverse = False

    # 把i这个数字加入到位图
    def fix(self, i: int) -> None:
        index = i // 32
        bit = i % 32
        if not self.reverse:
            # 位图所有位的状态，维持原始含义
            # 0 : 不存在
            # 1 : 存在
            if (self.set[index] & (1 << bit)) == 0:
                self.zeros -= 1
                self.ones += 1
                self.set[index] |= (1 << bit)
        else:
            # 位图所有位的状态，翻转了
            # 0 : 存在
            # 1 : 不存在
            if (self.set[index] & (1 << bit)) != 0:
                self.zeros -= 1
                self.ones += 1
                self.set[index] ^= (1 << bit)

    # 把i这个数字从位图中移除
    def unfix(self, i: int) -> None:
        index = i // 32
        bit = i % 32
        if not self.reverse:
            if (self.set[index] & (1 << bit)) != 0:
                self.ones -= 1
                self.zeros += 1
                self.set[index] ^= (1 << bit)
        else:
            if (self.set[index] & (1 << bit)) == 0:
                self.ones -= 1
                self.zeros += 1
                self.set[index] |= (1 << bit)

    def flip(self) -> None:
        self.reverse = not self.reverse
        tmp = self.zeros
        self.zeros = self.ones
        self.ones = tmp

    def all(self) -> bool:
        return self.ones == self.size

    def one(self) -> bool:
        return self.ones > 0

    def count(self) -> int:
        return self.ones

    def toString(self) -> str:
        builder = []
        i = 0
        for k in range(len(self.set)):
            number = self.set[k]
            for j in range(32):
                if i >= self.size:
                    break
                status = (number >> j) & 1
                status ^= 1 if self.reverse else 0
                builder.append(str(status))
                i += 1
        return ''.join(builder)