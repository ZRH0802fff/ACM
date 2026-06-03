class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        n = len(nums)
        if n == 0 or k == 0:
            return []
            
        # 对应 Java 的 int[] deque = new int[MAXN];
        # 预分配定长数组，速度远快于动态 append
        q = [0] * n
        h = 0
        t = 0
        
        m = n - k + 1
        ans = [0] * m
        
        # 1. 先形成长度为 k-1 的窗口
        for i in range(k - 1):
            # 维护单调递减：如果队尾元素 <= 当前元素，队尾出队
            while h < t and nums[q[t - 1]] <= nums[i]:
                t -= 1
            # 当前元素索引入队
            q[t] = i
            t += 1
            
        # 2. 当前窗口长度补齐为 k，并开始同步滑动
        for l in range(m):
            r = l + k - 1
            
            # 少一个，要让 r 位置的数进来
            while h < t and nums[q[t - 1]] <= nums[r]:
                t -= 1
            q[t] = r
            t += 1
            
            # 收集答案：队头永远是当前窗口的最大值
            ans[l] = nums[q[h]]
            
            # l 位置的数即将滑出窗口，如果队头刚好是 l，让队头出队
            if q[h] == l:
                h += 1
                
        return ans