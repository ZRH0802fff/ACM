class MinStack:

    def __init__(self):
        self.data = []           # 数据栈
        self.min_stack = []      # 辅助栈，记录当前最小值（单调不增）

    def push(self, val: int) -> None:
        self.data.append(val)
        
        # 如果辅助栈为空 或者  val <= 当前最小值，则压入 val
        if not self.min_stack or val <= self.min_stack[-1]:
            self.min_stack.append(val)
        else:
            # 否则重复压入当前最小值（保持与 data 栈等长）
            self.min_stack.append(self.min_stack[-1])

    def pop(self) -> None:
        if self.data:
            self.data.pop()
            self.min_stack.pop()

    def top(self) -> int:
        if self.data:
            return self.data[-1]
        # LeetCode 保证不会在空栈调用 top/getMin，可不写异常处理
        return 0  # 或 raise Exception

    def getMin(self) -> int:
        if self.min_stack:
            return self.min_stack[-1]
        return 0  # 或 raise Exception