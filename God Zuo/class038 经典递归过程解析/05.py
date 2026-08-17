# 用递归函数逆序栈
# 思路：通过递归“挖出”栈底元素 → 逆序剩余栈 → 把挖出的元素压回（变成新栈顶）

class Solution:
    def reverse(self, stack):
        """
        主函数：逆序整个栈
        - 如果栈空，直接返回
        - 否则挖出栈底 num
        - 递归逆序剩余栈
        - 把 num 压回去（现在它变成栈顶了）
        """
        if not stack:
            return
        num = self.bottom_out(stack)
        self.reverse(stack)
        stack.append(num)

    def bottom_out(self, stack):
        """
        辅助函数：挖出栈底元素并返回
        - 弹出当前栈顶 ans
        - 如果栈空了，ans 就是栈底，返回它
        - 否则递归挖更深的栈底 last
        - 把 ans 压回去（恢复中间元素）
        - 返回 last（真正的栈底）
        """
        ans = stack.pop()
        if not stack:
            return ans
        last = self.bottom_out(stack)
        stack.append(ans)
        return last


# 测试代码
if __name__ == "__main__":
    stack = []
    stack.append(1)
    stack.append(2)
    stack.append(3)
    stack.append(4)
    stack.append(5)
    
    print("原始栈（从底到顶）：", stack)  # [1, 2, 3, 4, 5]
    
    s = Solution()
    s.reverse(stack)
    
    print("逆序后栈（从底到顶）：", stack)  # [5, 4, 3, 2, 1]
    
    print("从栈顶弹出顺序：")
    while stack:
        print(stack.pop())  # 1 2 3 4 5（逆序后弹出是原顺序倒过来）