# 用栈实现队列
# 用队列实现栈
from collections import deque


# 测试链接 : https://leetcode.cn/problems/implement-queue-using-stacks/
class MyQueue:

    def __init__(self):
        self.in_stack = []
        self.out_stack = []

    # 从 in 栈把数据倒到 out 栈
    # 只有 out 为空时才倒
    # 并且要把 in 全部倒完
    def _in_to_out(self):
        if not self.out_stack:
            while self.in_stack:
                self.out_stack.append(self.in_stack.pop())

    def push(self, x: int) -> None:
        self.in_stack.append(x)
        self._in_to_out()

    def pop(self) -> int:
        self._in_to_out()
        return self.out_stack.pop()

    def peek(self) -> int:
        self._in_to_out()
        return self.out_stack[-1]

    def empty(self) -> bool:
        return not self.in_stack and not self.out_stack


# 测试链接 : https://leetcode.cn/problems/implement-stack-using-queues/
class MyStack:

    def __init__(self):
        self.queue = deque()

    # 每次 push 都把新元素放到队尾，然后把前面所有元素轮转一遍
    # 时间复杂度 O(n)
    def push(self, x: int) -> None:
        n = len(self.queue)
        self.queue.append(x)
        for _ in range(n):
            self.queue.append(self.queue.popleft())

    def pop(self) -> int:
        return self.queue.popleft()

    def top(self) -> int:
        return self.queue[0]

    def empty(self) -> bool:
        return len(self.queue) == 0


# 如果你想写更高效的用队列实现栈（两个队列版本），可以参考下面这种写法（push O(1), pop O(1) 均摊）
class MyStack_Optimized:

    def __init__(self):
        self.main = deque()
        self.helper = deque()

    def push(self, x: int) -> None:
        self.main.append(x)

    def pop(self) -> int:
        # 把 main 除了最后一个元素外全部倒到 helper
        while len(self.main) > 1:
            self.helper.append(self.main.popleft())
        # 取出最后一个（即栈顶）
        res = self.main.popleft()
        # 交换引用，helper 变成新的 main
        self.main, self.helper = self.helper, self.main
        return res

    def top(self) -> int:
        while len(self.main) > 1:
            self.helper.append(self.main.popleft())
        res = self.main[0]
        self.helper.append(self.main.popleft())
        self.main, self.helper = self.helper, self.main
        return res

    def empty(self) -> bool:
        return len(self.main) == 0