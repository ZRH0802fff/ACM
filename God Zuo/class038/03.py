class Solution:
    def permute(self, nums):
        """
        无重复数字的全排列
        LeetCode 46. Permutations
        
        思路：原地交换 + 回溯
        - 从第 i 位开始，把剩余所有数轮流放到第 i 位
        - 交换后递归到 i+1
        - 递归回来后交换回去（恢复现场）
        """
        ans = []
        
        def f(i):
            if i == len(nums):
                # 当前 nums 就是一个完整排列，复制加入答案
                ans.append(nums[:])  # 必须切片复制
                return
            
            # 从 i 到末尾的每个数，都尝试放到第 i 位
            for j in range(i, len(nums)):
                # 交换
                nums[i], nums[j] = nums[j], nums[i]
                # 递归
                f(i + 1)
                # 回溯（恢复）
                nums[i], nums[j] = nums[j], nums[i]
        
        f(0)
        return ans
    
