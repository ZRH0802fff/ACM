class Solution:
    def reverse(self, stack):
        if not stack:
            return 
        last=self.bottom_out(stack)
        self.reverse(stack)
        stack.append(last)



    def bottom_out(self,stack):
        ans=stack.pop()
        if not stack :
            return ans
        last=self.bottom_out(stack)
        stack.append(ans)
        return last
    
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