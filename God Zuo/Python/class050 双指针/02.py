from typing import List

class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        # 边界防御：如果数组为空或长度不足 2，说明无法寻找重复
        if not nums or len(nums) < 2:
            return -1
            
        # 1. 初始化快慢指针
        # 慢指针走一步，快指针走两步
        slow = nums[0]
        fast = nums[nums[0]]
        
        # 2. 第一次相遇：寻找环内相遇点
        while slow != fast:
            slow = nums[slow]
            fast = nums[nums[fast]]
            
        # 3. 找环的入口（即重复的数字）
        # 快指针回到起点，这次快慢指针都每次只走一步
        fast = 0
        while slow != fast:
            fast = nums[fast]
            slow = nums[slow]
            
        # 再次相遇的点，就是环的入口（重复的数字）
        return slow