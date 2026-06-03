# 数组中两个数的最大异或值
# 给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0<=i<=j<=n
# 1 <= nums.length <= 2 * 10^5
# 0 <= nums[i] <= 2^31 - 1
# 测试链接 : https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/

class Code02_TwoNumbersMaximumXor:

    def __init__(self):         
        self.MAXN = 3000001
        self.tree = [[0] * 2 for _ in range(self.MAXN)]
        self.cnt = 0
        self.high = 0

    # 前缀树的做法（使用 self 实现实例方法和实例变量）
    def findMaximumXOR1(self, nums):
        self.build(nums)
        ans = 0
        for num in nums:
            ans = max(ans, self.maxXor(num))
        self.clear()
        return ans

    def build(self, nums):
        self.cnt = 1
        # 找个最大值
        max_val = float('-inf')
        for num in nums:
            max_val = max(num, max_val)
        # 计算数组最大值的二进制状态，有多少个前缀的0
        # 可以忽略这些前置的0，从left位开始考虑
        if max_val == 0:
            self.high = -1
        else:
            self.high = max_val.bit_length() - 1
        for num in nums:
            self.insert(num)

    def insert(self, num):
        cur = 1
        for i in range(self.high, -1, -1):
            path = (num >> i) & 1
            if self.tree[cur][path] == 0:
                self.cnt += 1
                self.tree[cur][path] = self.cnt
            cur = self.tree[cur][path]

    def maxXor(self, num):
        # 最终异或的结果(尽量大)
        ans = 0
        # 前缀树目前来到的节点编号
        cur = 1
        for i in range(self.high, -1, -1):
            # status : num第i位的状态
            status = (num >> i) & 1
            # want : num第i位希望遇到的状态
            want = status ^ 1
            if self.tree[cur][want] == 0:  # 询问前缀树，能不能达成
                # 不能达成
                want ^= 1
            # want变成真的往下走的路
            ans |= (status ^ want) << i
            cur = self.tree[cur][want]
        return ans

    def clear(self):
        for i in range(1, self.cnt + 1):
            self.tree[i][0] = self.tree[i][1] = 0

    # 用哈希表的做法（同样改成实例方法）
    def findMaximumXOR2(self, nums):
        max_val = float('-inf')
        for num in nums:
            max_val = max(num, max_val)
        ans = 0
        set_ = set()
        high = -1 if max_val == 0 else max_val.bit_length() - 1
        for i in range(high, -1, -1):
            # ans : 31....i+1 已经达成的目标
            better = ans | (1 << i)
            set_.clear()
            for num in nums:
                # num : 31.....i 这些状态保留，剩下全成0
                num = (num >> i) << i
                set_.add(num)
                # num ^ 某状态 是否能 达成better目标，就在set中找 某状态 : better ^ num
                if (better ^ num) in set_:
                    ans = better
                    break
        return ans