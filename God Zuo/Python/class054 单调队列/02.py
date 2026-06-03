class Solution:
    def longestSubarray(self, nums: list[int], limit: int) -> int:
        self.nums = nums
        n = len(nums)
        
        # 将原 Java 中的 static 变量绑定到 self 实例上，供其他函数共享
        self.max_q = [0] * n
        self.min_q = [0] * n
        self.max_h = 0
        self.max_t = 0
        self.min_h = 0
        self.min_t = 0
        
        ans = 0
        r = 0
        for l in range(n):
            # [l, r)，r 永远是没有进入窗口的、下一个数所在的位置
            while r < n and self.ok(limit, nums[r]):
                self.push(r)
                r += 1
            
            # 从 while 出来的时候，[l, r) 是 l 开头的子数组能向右延伸的最大范围
            length = r - l
            if length > ans:
                ans = length
                
            self.pop(l)
            
        return ans

    # 判断如果加入数字 number，窗口最大值 - 窗口最小值是否依然 <= limit
    def ok(self, limit: int, number: int) -> bool:
        # max : 如果 number 进来，新窗口的最大值
        max_val = number
        if self.max_h < self.max_t and self.nums[self.max_q[self.max_h]] > number:
            max_val = self.nums[self.max_q[self.max_h]]
            
        # min : 如果 number 进来，新窗口的最小值
        min_val = number
        if self.min_h < self.min_t and self.nums[self.min_q[self.min_h]] < number:
            min_val = self.nums[self.min_q[self.min_h]]
            
        return max_val - min_val <= limit

    # r 位置的数字进入窗口，修改窗口内最值的更新结构
    def push(self, r: int):
        # 维护最大值队列
        while self.max_h < self.max_t and self.nums[self.max_q[self.max_t - 1]] <= self.nums[r]:
            self.max_t -= 1
        self.max_q[self.max_t] = r
        self.max_t += 1
        
        # 维护最小值队列
        while self.min_h < self.min_t and self.nums[self.min_q[self.min_t - 1]] >= self.nums[r]:
            self.min_t -= 1
        self.min_q[self.min_t] = r
        self.min_t += 1

    # 窗口要吐出 l 位置的数了，检查过期！
    def pop(self, l: int):
        if self.max_h < self.max_t and self.max_q[self.max_h] == l:
            self.max_h += 1
        if self.min_h < self.min_t and self.min_q[self.min_h] == l:
            self.min_h += 1