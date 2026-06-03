from typing import List

class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        l = 0
        r = len(nums)
        
        while l < r:
            # 1. 恰好是我们要的数字，并且就在正确的位置上
            if nums[l] == l + 1:
                l += 1
                
            # 2. 发现“垃圾”数字，直接把它丢到垃圾区 (r 的右边)
            # 什么是垃圾？
            # - nums[l] <= l : 是负数、0，或者是前面已经收集过的重复小数字
            # - nums[l] > r  : 数字太大了，超出了我们期望能收集的最大正整数范围
            # - nums[nums[l] - 1] == nums[l] : 数字合法，但它该去的位置上已经有一个同样的数字了（发现了重复）
            elif nums[l] <= l or nums[l] > r or nums[nums[l] - 1] == nums[l]:
                r -= 1
                # 把垃圾丢到 r 的位置，把原来 r 位置的未知数字换过来继续检查
                nums[l], nums[r] = nums[r], nums[l]
                
            # 3. 数字合法，且不是垃圾，只是当前位置不对，把它“发货”到它该去的地方
            else:
                # ⚠️ Python 避  坑指南：这里最好把目标索引单独提出来
                target_idx = nums[l] - 1
                nums[l], nums[target_idx] = nums[target_idx], nums[l]
                
        # 经过发货和垃圾回收，l 的左边一定都是连续的正整数
        # 所以缺失的第一个正整数就是 l + 1
        return l + 1