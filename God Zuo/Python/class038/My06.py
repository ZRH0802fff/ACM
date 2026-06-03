import random

class Solution:
    def sort(self, stack):
        h=self.a(stack)
        while h>0:
            ma=self.b(stack,h)
            times=self.c(stack,h,ma)  
            self.d(stack,h,ma,times)
            h-=times


    def a(self,stack):
        if not stack:
            return 0
        num=stack.pop()
        h=self.a(stack)+1
        stack.append(num)
        return h
    
    def b(self,stack,h):
        if h==0:
            return float('-inf')
        num=stack.pop()
        rm=self.b(stack,h-1)
        m=max(rm,num)
        stack.append(num)
        return m
    
    def c(self,stack,h,ma):
        if h==0:
            return 0
        num=stack.pop()
        rt=self.c(stack,h-1,ma)+(1 if num==ma else 0)
        stack.append(num)
        return rt
    
    def d (self,stack,h,ma,times):
        if h==0:
            for i in range(times):
                stack.append(ma)
            return
        num=stack.pop()
        self.d(stack,h-1,ma,times)
        if num!=ma:
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