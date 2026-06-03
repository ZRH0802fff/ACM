class MyCircularDeque:

    def __init__(self, k: int):
        self.deque = [0] * k
        self.limit = k
        self.size = 0
        self.left = 0
        self.right = 0

    def insertFront(self, value: int) -> bool:
        if self.isFull():
            return False
        
        if self.isEmpty():
            self.left = self.right = 0
            self.deque[0] = value
        else:
            self.left = (self.left - 1 + self.limit) % self.limit
            self.deque[self.left] = value
        
        self.size += 1
        return True

    def insertLast(self, value: int) -> bool:
        if self.isFull():
            return False
        
        if self.isEmpty():
            self.left = self.right = 0
            self.deque[0] = value
        else:
            self.right = (self.right + 1) % self.limit
            self.deque[self.right] = value
        
        self.size += 1
        return True

    def deleteFront(self) -> bool:
        if self.isEmpty():
            return False
        
        self.left = (self.left + 1) % self.limit
        self.size -= 1
        return True

    def deleteLast(self) -> bool:
        if self.isEmpty():
            return False
        
        self.right = (self.right - 1 + self.limit) % self.limit
        self.size -= 1
        return True

    def getFront(self) -> int:
        if self.isEmpty():
            return -1
        return self.deque[self.left]

    def getRear(self) -> int:
        if self.isEmpty():
            return -1
        return self.deque[self.right]

    def isEmpty(self) -> bool:
        return self.size == 0

    def isFull(self) -> bool:
        return self.size == self.limit