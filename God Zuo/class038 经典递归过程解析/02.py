class Solution:
    def subsetsWithDup(self, nums):
        """
        给定一个可能包含重复元素的整数数组 nums，返回所有可能的子集（幂集）
        要求：答案中不能包含重复的子集
        
        思路：
        1. 先对数组排序，让相同的元素挨在一起
        2. 使用“按组处理重复元素”的方式，避免产生重复组合
        3. 对于每一组相同的数，选择出现 0 次、1 次、2 次……直到该组结束
        4. 使用 path 数组记录当前选择的元素，回溯时通过 size 控制长度
        
        示例：
        nums = [1,2,2]
        输出：[[], [1], [1,2], [1,2,2], [2], [2,2]]
        """
        ans = []
        nums.sort()           # 必须排序，让重复元素相邻
        path = [0] * len(nums)  # 路径数组，足够大
        
        def f(i, size):
            # 到达数组末尾，收集当前路径（0 ~ size-1）
            if i == len(nums):
                # 把 path[0..size) 复制到结果中
                ans.append(path[:size][:])   # 浅拷贝
                return
            
            # 找到当前这一组重复元素的结束位置（下一组第一个）
            j = i + 1
            while j < len(nums) and nums[j] == nums[i]:
                j += 1
            
            # 选择：当前这一组的数，出现 0 次
            f(j, size)
            
            # 选择：当前这一组的数，出现 1 次、2 次、... 直到组结束
            for k in range(i, j):
                path[size] = nums[k]
                f(j, size + 1)
                size += 1   # 注意：这里 size 是累加的，但因为是值传递，下层不影响上层
        
        f(0, 0)
        return ans