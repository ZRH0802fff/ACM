class Solution:
    def permuteUnique(self, nums):
        """
        有重复数字的全排列（去重）
        LeetCode 47. Permutations II
        
        思路：原地交换 + 同一层去重
        - 排序后（可选，但这里没排序，用 set 替代）
        - 在同一层（for 循环），用 set 记录已经尝试过的数字
        - 只有没出现过的数字才交换到 i 位置进行递归
        """
        ans = []
        
        def f(i):
            if i == len(nums):
                # 当前 nums 是一个有效排列，复制加入答案
                ans.append(nums[:])
                return
            
            # 同一层去重：记录已经交换到 i 位置的数字值
            seen = set()
            
            for j in range(i, len(nums)):
                # 如果这个值已经尝试过，就跳过（避免重复排列）
                if nums[j] in seen:
                    continue
                seen.add(nums[j])
                
                # 交换，把 nums[j] 放到第 i 位
                nums[i], nums[j] = nums[j], nums[i]
                # 递归到下一层
                f(i + 1)
                # 回溯恢复
                nums[i], nums[j] = nums[j], nums[i]
        
        f(0)
        return ans