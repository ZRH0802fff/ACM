# 用递归函数排序栈
# 栈只提供 append (push), pop, len(stack)==0 (isEmpty) 方法
# 请完成无序栈的排序，要求排完序之后，从栈顶到栈底从小到大
# 只能使用栈提供的 append/pop/len==0，以及递归函数
# 除此之外不能使用任何的容器，数组也不行

import random

class Solution:
    def sort(self, stack):
        """
        主函数：排序栈，从顶到底从小到大（弹出顺序从小到大）
        
        思路：
        1. 求当前栈深度 deep
        2. while deep > 0:
           - 找 top deep 层中的 max
           - 统计 max 出现次数 k
           - 把这 k 个 max 沉底（down 函数）
           - deep -= k （因为 max 已沉底，剩余部分深度减 k）
        """
        deep_val = self.deep(stack)
        while deep_val > 0:
            max_val = self.max_val(stack, deep_val)
            k = self.times(stack, deep_val, max_val)
            self.down(stack, deep_val, max_val, k)
            deep_val -= k

    def deep(self, stack):
        """
        返回栈的深度，不改变栈
        - 如果空，返回 0
        - 否则弹出 num，递归 deep + 1，压回 num
        """
        if not stack:
            return 0
        num = stack.pop()
        deep_val = self.deep(stack) + 1
        stack.append(num)
        return deep_val

    def max_val(self, stack, deep):
        """
        从顶往下 deep 层，返回最大值，不改变栈
        """
        if deep == 0:
            return float('-inf')
        num = stack.pop()
        rest_max = self.max_val(stack, deep - 1)
        max_v = max(num, rest_max)
        stack.append(num)
        return max_v

    def times(self, stack, deep, max_v):
        """
        从顶往下 deep 层，返回 max_v 出现次数，不改变栈
        """
        if deep == 0:
            return 0
        num = stack.pop()
        rest_times = self.times(stack, deep - 1, max_v)
        times_val = rest_times + (1 if num == max_v else 0)
        stack.append(num)
        return times_val

    def down(self, stack, deep, max_v, k):
        """
        从顶往下 deep 层，把 k 个 max_v 沉底，剩余不变
        - 如果 deep==0，到底了，压入 k 个 max_v
        - 否则弹出 num，递归 down(deep-1)
        - 如果 num != max_v，压回 num（max_v 已过滤）
        """
        if deep == 0:
            for _ in range(k):
                stack.append(max_v)
        else:
            num = stack.pop()
            self.down(stack, deep - 1, max_v, k)
            if num != max_v:
                stack.append(num)

# 为了测试
# 生成随机栈
def random_stack(n, v):
    ans = []
    for _ in range(n):
        ans.append(random.randint(0, v - 1))
    return ans

# 为了测试
# 检测栈是不是从顶到底从小到大（弹出顺序从小到大）
def is_sorted(stack):
    step = float('-inf')
    while stack:
        if step > stack[-1]:  # peek 用 stack[-1]
            return False
        step = stack.pop()
    return True

# 为了测试
if __name__ == "__main__":
    # 固定测试
    test = []
    test.append(1)
    test.append(5)
    test.append(4)
    test.append(5)
    test.append(3)
    test.append(2)
    test.append(3)
    test.append(1)
    test.append(4)
    test.append(2)
    
    s = Solution()
    s.sort(test)
    
    while test:
        print(test.pop())

    # 随机测试
    N = 20
    V = 20
    test_times = 20000
    print("测试开始")
    for _ in range(test_times):
        n = random.randint(0, N)
        stack = random_stack(n, V)
        s.sort(stack)
        if not is_sorted(stack):
            print("出错了!")
            break
    print("测试结束")