import heapq

class Solution:
    # 方法1：使用Python内置的堆（小根堆，通过取负数模拟大根堆）
    def halveArray1(self, nums: list[int]) -> int:
        # 大根堆：Python的heapq是小根堆，所以存负数来模拟大根堆
        heap = []
        total_sum = 0
        
        for num in nums:
            # 存负数，这样最大的数会变成最小的负数，位于堆顶
            heapq.heappush(heap, -num)
            total_sum += num
        
        # 目标：减少一半的累加和
        target = total_sum / 2
        operations = 0
        reduced = 0  # 已经减少的量
        
        while reduced < target:
            # 取出当前最大的数（最负的负数）
            cur = -heapq.heappop(heap)
            half = cur / 2
            reduced += half
            operations += 1
            # 将减半后的数放回堆中
            heapq.heappush(heap, -half)
        
        return operations

    # 方法2：手动实现大根堆（更高效，避免浮点数精度问题）
    MAXN = 100001
    
    def halveArray2(self, nums: list[int]) -> int:
        n = len(nums)
        # 使用移位来避免浮点数，左移20位相当于乘以 2^20
        self.heap = [0] * self.MAXN
        self.size = n
        
        total_sum = 0
        # 初始化堆，从最后一个非叶子节点开始建堆
        for i in range(n - 1, -1, -1):
            self.heap[i] = nums[i] << 20  # 左移20位
            total_sum += self.heap[i]
            self._heapify(i)
        
        target = total_sum // 2
        operations = 0
        reduced = 0
        
        while reduced < target:
            self.heap[0] //= 2  # 堆顶元素减半
            reduced += self.heap[0]
            operations += 1
            self._heapify(0)  # 重新调整堆
        
        return operations
    
    def _heapify(self, i: int):
        """向下调整堆，维护大根堆性质"""
        left = i * 2 + 1
        while left < self.size:
            # 找出左右子节点中较大的那个
            best = left
            if left + 1 < self.size and self.heap[left + 1] > self.heap[left]:
                best = left + 1
            
            # 比较父节点和较大的子节点
            if self.heap[best] <= self.heap[i]:
                break
            
            self._swap(best, i)
            i = best
            left = i * 2 + 1
    
    def _swap(self, i: int, j: int):
        """交换堆中两个元素"""
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]


# 测试代码
if __name__ == "__main__":
    sol = Solution()
    
    # 测试用例
    nums1 = [5, 19, 8, 1]
    print(f"nums = {nums1}")
    print(f"方法1结果: {sol.halveArray1(nums1.copy())}")
    print(f"方法2结果: {sol.halveArray2(nums1)}")
    
    print()
    
    nums2 = [3, 8, 20]
    print(f"nums = {nums2}")
    print(f"方法1结果: {sol.halveArray1(nums2.copy())}")
    print(f"方法2结果: {sol.halveArray2(nums2)}")