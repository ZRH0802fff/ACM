from typing import List

class Solution:
    # 辅助数组的解法（非最优解）
    # 时间复杂度 O(n)，额外空间复杂度 O(n)
    def trap1(self, nums: List[int]) -> int:
        if not nums or len(nums) < 3:
            return 0
            
        n = len(nums)
        lmax = [0] * n
        rmax = [0] * n
        
        # 0 ~ i 范围上的最大值，记录在 lmax[i]
        lmax[0] = nums[0]
        for i in range(1, n):
            lmax[i] = max(lmax[i - 1], nums[i])
            
        # i ~ n-1 范围上的最大值，记录在 rmax[i]
        rmax[n - 1] = nums[n - 1]
        for i in range(n - 2, -1, -1):
            rmax[i] = max(rmax[i + 1], nums[i])
            
        ans = 0
        # 第 0 个和第 n-1 个位置边缘是存不住水的，从 1 遍历到 n-2
        for i in range(1, n - 1):
            ans += max(0, min(lmax[i - 1], rmax[i + 1]) - nums[i])
            
        return ans

    # 双指针的解法（最优解）
    # 时间复杂度 O(n)，额外空间复杂度 O(1)
    def trap(self, nums: List[int]) -> int:
        if not nums or len(nums) < 3:
            return 0
            
        # 初始化左右指针和左右两侧的最大值记录
        l = 1
        r = len(nums) - 2
        lmax = nums[0]
        rmax = nums[-1]
        
        ans = 0
        
        # 指针相遇前不断向内收缩
        while l <= r:
            # 谁小结算谁，因为存水量是由短板决定的
            if lmax <= rmax:
                # 结算左侧当前位置的水量
                ans += max(0, lmax - nums[l])
                # 更新左侧历史最大值，并移动左指针
                lmax = max(lmax, nums[l])
                l += 1
            else:
                # 结算右侧当前位置的水量
                ans += max(0, rmax - nums[r])
                # 更新右侧历史最大值，并移动右指针
                rmax = max(rmax, nums[r])
                r -= 1
                
        return ans