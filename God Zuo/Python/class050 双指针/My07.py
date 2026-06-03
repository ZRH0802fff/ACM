# 测试链接 : https://leetcode.cn/problems/first-missing-positive/
from typing import List

class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        l,r=0,len(nums)
        while l<r:
            if nums[l]==l+1:
                l+=1
            elif nums[l]<=l or nums[l]>r or nums[nums[l]-1]==nums[l]:
                nums[l],nums[r-1]=nums[r-1],nums[l]
                r-=1
            else:
                idx=nums[l]-1
                nums[l],nums[idx]=nums[idx],nums[l]
# ====================================================================================
# 🚨 Python 原地交换避坑指南 (为什么一定要加 idx 变量)
# ====================================================================================
# 【千万别写成】： nums[l], nums[nums[l] - 1] = nums[nums[l] - 1], nums[l]
#
# 假设 nums = [4, 1, 2, 3], 当前 l = 0:
# Python 执行 a, b = c, d 时，是【从左到右】依次给 a 和 b 赋值的！
# 1. 右边准备好的值是 (3, 4)
# 2. 首先执行：nums[l] = 3 (即 nums[0] = 3)。此时数组瞬间变成 [3, 1, 2, 3]
# 3. 接着执行：nums[nums[l] - 1] = 4
#    - 💥 灾难发生：因为 nums[0] 刚才被改成了 3，所以这里计算出的索引变成了 3 - 1 = 2！
#    - 实际执行成了 nums[2] = 4。导致无辜的 2 被覆盖，结果错乱甚至越界！
#
# 【正确解法】：
# 老老实实把“目标索引”提前算好并存下来，锁死它，彻底杜绝动态取值带来的副作用。
# 也可以炫技一下
# nums[nums[l] - 1], nums[l] = nums[l], nums[nums[l] - 1]
# ====================================================================================                
        return r+1