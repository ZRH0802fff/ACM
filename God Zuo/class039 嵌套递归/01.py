# 含有嵌套的表达式求值
# 支持 + - * / 和括号嵌套
# LeetCode 772. Basic Calculator III（会员题）
# 牛客网链接：https://www.nowcoder.com/practice/c215ba61c8b1443b996351df929dc4d4

class Solution:
    def calculate(self, s: str) -> int:
        self.where = 0
        chars = list(s.replace(" ", ""))  # 去除空格，转为字符列表
        return self.f(chars, 0)

    def f(self, s: list, i: int) -> int:
        """
        从 s[i] 开始计算，直到遇到 ')' 或字符串结束
        返回：当前这一段表达式的值
        通过 self.where 更新全局位置，让上层知道从哪里继续
        """
        cur = 0
        numbers = []
        ops = []

        while i < len(s) and s[i] != ')':
            ch = s[i]

            if ch.isdigit():
                # 累积多位数字
                cur = cur * 10 + int(ch)
                i += 1

            elif ch == '(':
                # 遇到左括号，递归计算括号内的值
                cur = self.f(s, i + 1)
                i = self.where + 1  # 更新 i 到 ) 的下一个位置

            else:
                # 遇到运算符 + - * /
                self.push(numbers, ops, cur, ch)
                cur = 0
                i += 1

        # 处理最后一个数字（用 + 模拟压入）
        self.push(numbers, ops, cur, '+')

        self.where = i  # 更新全局位置
        return self.compute(numbers, ops)

    def push(self, numbers: list, ops: list, cur: int, op: str):
        """
        把当前数字和运算符压入
        如果栈顶是 * 或 /，立即计算（优先级更高）
        """
        if not numbers or ops[-1] in '+-':
            numbers.append(cur)
            ops.append(op)
        else:
            # 栈顶是 * 或 /，立即计算
            top_num = numbers.pop()
            top_op = ops.pop()
            if top_op == '*':
                numbers.append(top_num * cur)
            else:
                numbers.append(top_num // cur)  # 注意：整数除法，向零取整
            ops.append(op)

    def compute(self, numbers: list, ops: list) -> int:
        """
        只剩 + - 的加减法，从左到右计算
        """
        if not numbers:
            return 0

        ans = numbers[0]
        for i in range(1, len(numbers)):
            if ops[i - 1] == '+':
                ans += numbers[i]
            else:
                ans -= numbers[i]
        return ans


# 测试代码
if __name__ == "__main__":
    solution = Solution()
    
    test_cases = [
        "1 + 1",
        " 2-1 + 2 ",
        "(1+(4+5+2)-3)+(6+8)",
        "2*(5+5*2)/3+(6/2+8)",
        "(2+6*3+5-(3*14/7+2)*5)+3",
        "1-(     -2)",
    ]
    
    for expr in test_cases:
        result = solution.calculate(expr)
        print(f"{expr} = {result}")