from typing import List

class Solution:
    def sortArrayByParityII(self, nums: List[int]) -> List[int]:
        n = len(nums)
        odd = 1
        even = 0
        
        # 当 odd 和 even 都没有越界时继续
        # 因为奇数和偶数数量刚好各一半，只要其中一个越界，说明所有的坑位都已经填对了
        while odd < n and even < n:
            # 检查最后一个元素 nums[-1] 的奇偶性
            if nums[-1] & 1 == 1:
                # 如果是奇数，和当前的 odd 指针位置交换，然后 odd 指针跳 2 步
                nums[odd], nums[-1] = nums[-1], nums[odd]
                odd += 2
            else:
                # 如果是偶数，和当前的 even 指针位置交换，然后 even 指针跳 2 步
                nums[even], nums[-1] = nums[-1], nums[even]
                even += 2
                
        return nums