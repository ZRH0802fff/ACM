from typing import List

class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        
        # 内部辅助函数：计算以 speed 速度吃完所有香蕉需要耗费的小时数
        def get_hours(speed: int) -> int:
            # (pile + speed - 1) // speed 是极速向上取整的整数运算写法
            # 等价于 math.ceil(pile / speed)
            return sum((pile + speed - 1) // speed for pile in piles)

        # 速度的最小可能值是 1（题目要求 k 为正整数）
        l = 1
        # 速度的最大可能值是香蕉堆中的最大值
        # 因为一小时最多只能吃一堆，速度再大也没有意义
        r = max(piles) 
        
        ans = 0
        
        # 开始在 [l, r] 范围内进行二分查找
        while l <= r:
            # Python 底层支持大整数，不存在 32 位整型溢出问题
            # 所以直接 (l + r) // 2 即可，不需要像 Java 那样写 l + (r - l) / 2
            m = (l + r) // 2 
            
            if get_hours(m) <= h:
                # 达标！说明能在 h 小时内吃完
                # 先把当前达标的速度记录下来作为备选答案
                ans = m
                # 珂珂喜欢慢慢吃，所以我们去左侧区间 [l, m-1] 尝试寻找更慢且达标的速度
                r = m - 1
            else:
                # 不达标！说明吃太慢了，导致超时
                # 必须提高速度，去右侧区间 [m+1, r] 寻找
                l = m + 1
                
        return ans