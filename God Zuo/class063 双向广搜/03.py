import bisect

class Solution:
    def minAbsDifference(self, nums: list[int], goal: int) -> int:
        # 1. 极限值剪枝 (提前预判天花板和地板)
        # 如果 goal 极大或极小，连所有正数/所有负数加起来都够不到
        # 那直接返回极限差距即可，一步到位！
        min_sum = sum(x for x in nums if x < 0)
        max_sum = sum(x for x in nums if x > 0)
        
        if max_sum < goal:
            return goal - max_sum
        if min_sum > goal:
            return min_sum - goal
            
        # 2. 折半拆分
        n = len(nums)
        left = nums[:n // 2]
        right = nums[n // 2:]
        
        # 3. 状态生成与自动去重 (Python 绝招)
        # 使用 set 不仅能无缝推导，还能自动吃掉因为重复元素（如多个 1）导致的重复状态
        # 完美替代了原 Java 代码中复杂的 while(nums[j] == nums[i]) 去重逻辑
        lsum = {0}
        for x in left:
            lsum |= {s + x for s in lsum}
            
        rsum = {0}
        for x in right:
            rsum |= {s + x for s in rsum}
            
        # 4. 转换为有序列表，准备二分查找
        # 排序后，底层变为 C 数组，后续的 bisect 速度会极快
        lsum = sorted(lsum)
        rsum = sorted(rsum)
        
        ans = float('inf')
        
        # 5. 遍历左半边，二分查找右半边
        # 对于左边的每一个 val，我们在右边找一个最接近 goal - val 的数字
        for val in lsum:
            target = goal - val
            idx = bisect.bisect_left(rsum, target)
            
            # 情况 A：插入点右边的值（>= target）
            if idx < len(rsum):
                ans = min(ans, abs(target - rsum[idx]))
                
            # 情况 B：插入点左边的值（< target）
            if idx > 0:
                ans = min(ans, abs(target - rsum[idx - 1]))
                
            # 极致剪枝：如果已经找到了完美匹配（误差为0），直接提前下班
            if ans == 0:
                return 0
                
        return ans