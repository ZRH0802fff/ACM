from typing import List

class Solution:
    def splitArray(self, nums: List[int], k: int) -> int:
        
        # 内部辅助函数：如果强制要求每个子数组的和都 <= limit
        # 请问至少需要把数组划分成几个部分？
        def get_parts(limit: int) -> int:
            parts = 1
            current_sum = 0
            
            for num in nums:
                # 极端情况：如果数组里有一个单独的元素已经大于 limit 了
                # 那无论怎么划分都不可能满足条件，直接返回无限大
                if num > limit:
                    return float('inf')
                    
                # 如果加上当前元素超出了 limit，说明必须在这里切一刀
                if current_sum + num > limit:
                    parts += 1
                    current_sum = num  # 新的部分从当前元素开始累加
                else:
                    current_sum += num
                    
            return parts

        # 二分的左边界 l 可以从 0 开始
        # (更优的下界其实是 max(nums)，但 0 也能依靠 get_parts 里的 infinity 拦截掉)
        l = 0
        # 二分的右边界 r 是数组全部元素的累加和（相当于完全不分割，k=1）
        r = sum(nums)
        
        ans = 0
        
        # [l, r] 范围内不停二分
        while l <= r:
            m = (l + r) // 2
            
            # 如果划分的部分数 <= k，说明当前给的 limit 足够宽裕（甚至给的太大了）
            # 我们记录下这个达标的 limit，并尝试去左边找找看有没有更小的
            if get_parts(m) <= k:
                ans = m
                r = m - 1
            else:
                # 划分的部分数 > k，说明 limit 给得太苛刻了，切得太碎了
                # 必须放宽限制，去右边找更大的 limit
                l = m + 1
                
        return ans