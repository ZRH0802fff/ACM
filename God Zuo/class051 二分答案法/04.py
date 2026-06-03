from typing import List

class Solution:
    def smallestDistancePair(self, nums: List[int], k: int) -> int:
        # 1. 必须先排序，这是后续使用双指针和二分的前提
        nums.sort()
        n = len(nums)
        
        # 内部辅助函数：统计差值 <= limit 的数对一共有多少个
        # 时间复杂度 O(N)
        def count_pairs(limit: int) -> int:
            count = 0
            r = 0
            # 枚举左边界 l
            for l in range(n):
                # 如果右边界 r 的下一个数和 l 的差值还没超标，右边界就一直往右扩
                while r + 1 < n and nums[r + 1] - nums[l] <= limit:
                    r += 1
                    
                # 此时 [l, r] 范围内的所有数，和 nums[l] 的差值都 <= limit
                # 产生的合法数对有：(l, l+1), (l, l+2) ... (l, r)
                # 数量刚好就是 r - l
                count += r - l
                
            return count

        # 2. 二分答案
        # 最小差值是 0 (任意两个相同的数)
        # 最大差值是排序后 最后一个数 和 第一个数 的差
        l = 0
        r = nums[-1] - nums[0]
        ans = 0
        
        while l <= r:
            m = (l + r) // 2
            
            # 如果差值 <= m 的数对数量 >= k
            # 说明我们猜的差值 m 可能给得太宽松了（或者刚好命中）
            # 记录当前达标的 m，并尝试去左边找更小的差值
            if count_pairs(m) >= k:
                ans = m
                r = m - 1
            else:
                # 数量不够 k 个，说明差值给得太苛刻了，必须放宽限制
                l = m + 1
                
        return ans