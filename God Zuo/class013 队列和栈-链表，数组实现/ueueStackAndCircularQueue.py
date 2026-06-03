from collections import deque
# class013 - Queue, Stack 和循环队列的各种实现方式

class Queue1:
    """使用 Python 内置的 collections.deque 双端队列 性能非常好"""
    from collections import deque
    
    def __init__(self):
        self.queue = deque()
    
    def is_empty(self):
        return len(self.queue) == 0
    
    def offer(self, num: int):
        """向队尾加入元素"""
        self.queue.append(num)
    
    def poll(self) -> int:
        """从队首弹出元素"""
        return self.queue.popleft()
    
    def peek(self) -> int:
        """查看队首元素（不弹出）"""
        return self.queue[0]
    
    def size(self) -> int:
        return len(self.queue)


class Queue2:
    """使用固定大小数组实现队列（最常见笔试/面试写法）"""
    
    def __init__(self, n: int):
        """n 为加入操作的总次数上限"""
        self.queue = [0] * n
        self.l = 0
        self.r = 0
    
    def is_empty(self) -> bool:
        return self.l == self.r
    
    def offer(self, num: int):
        self.queue[self.r] = num
        self.r += 1
    
    def poll(self) -> int:
        val = self.queue[self.l]
        self.l += 1
        return val
    
    def head(self) -> int:
        return self.queue[self.l]
    
    def tail(self) -> int:
        return self.queue[self.r - 1]
    
    def size(self) -> int:
        return self.r - self.l


class Stack1:
    """使用 Python 内置 list 作为栈（最常用）"""
    
    def __init__(self):
        self.stack = []
    
    def is_empty(self) -> bool:
        return len(self.stack) == 0
    
    def push(self, num: int):
        self.stack.append(num)
    
    def pop(self) -> int:
        return self.stack.pop()
    
    def peek(self) -> int:
        return self.stack[-1]
    
    def size(self) -> int:
        return len(self.stack)


class Stack2:
    """使用固定大小数组实现栈（空间复用版本）"""
    
    def __init__(self, n: int):
        """n 为栈中同时存在的元素个数上限"""
        self.stack = [0] * n
        self.size = 0
    
    def is_empty(self) -> bool:
        return self.size == 0
    
    def push(self, num: int):
        self.stack[self.size] = num
        self.size += 1
    
    def pop(self) -> int:
        self.size -= 1
        return self.stack[self.size]
    
    def peek(self) -> int:
        return self.stack[self.size - 1]
    
    def size(self) -> int:
        return self.size


class MyCircularQueue:
    """LeetCode 622. 设计循环队列"""
    
    def __init__(self, k: int):
        """k 为队列的最大容量"""
        self.queue = [0] * k
        self.l = 0
        self.r = 0
        self.size = 0
        self.limit = k
    
    def enQueue(self, value: int) -> bool:
        if self.isFull():
            return False
        
        self.queue[self.r] = value
        self.r = 0 if self.r == self.limit - 1 else self.r + 1
        self.size += 1
        return True
    
    def deQueue(self) -> bool:
        if self.isEmpty():
            return False
        
        self.l = 0 if self.l == self.limit - 1 else self.l + 1
        self.size -= 1
        return True
    
    def Front(self) -> int:
        if self.isEmpty():
            return -1
        return self.queue[self.l]
    
    def Rear(self) -> int:
        if self.isEmpty():
            return -1
        # 计算最后一个元素的位置
        last = self.limit - 1 if self.r == 0 else self.r - 1
        return self.queue[last]
    
    def isEmpty(self) -> bool:
        return self.size == 0
    
    def isFull(self) -> bool:
        return self.size == self.limit


# 测试用例（可选）
if __name__ == "__main__":
    q = MyCircularQueue(3)
    print(q.enQueue(1))  # True
    print(q.enQueue(2))  # True
    print(q.enQueue(3))  # True
    print(q.enQueue(4))  # False
    print(q.Rear())      # 3
    print(q.isFull())    # True
    print(q.deQueue())   # True
    print(q.enQueue(4))  # True
    print(q.Rear())      # 4