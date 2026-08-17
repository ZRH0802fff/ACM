from typing import List

def minSubarray(nums: List[int], p: int) -> int:
    # 计算整个数组的总和对 p 的余数
    total_mod = 0
    for num in nums:
        total_mod = (total_mod + num) % p
    
    # 如果总和本身就能被 p 整除，直接返回 0（不需要移除任何子数组）
    if total_mod == 0:
        return 0
    
    # key: 前缀和 % p 的余数
    # value: 该余数最晚出现的位置（下标）
    prefix_map = {0: -1}
    ans = float('inf')          # 记录最短需要移除的子数组长度
    cur = 0                     # 当前前缀和 % p
    
    for i in range(len(nums)):
        cur = (cur + nums[i]) % p
        
        # 我们需要找到一个前缀和余数 find，使得 (cur - find) % p == total_mod
        # 即 find = (cur - total_mod) % p
        find = (cur - total_mod + p) % p
        
        # 如果找到符合条件的之前的余数，更新最短长度
        if find in prefix_map:
            ans = min(ans, i - prefix_map[find])
        
        # 更新当前余数的最晚出现位置
        prefix_map[cur] = i
    
    # 如果 ans 仍然是初始值，说明无法找到符合条件的子数组
    # 或者找到的长度等于整个数组长度（不允许移除整个数组）
    return -1 if ans == float('inf') or ans == len(nums) else ans


# ==================== 测试示例 ====================
if __name__ == "__main__":
    # 示例 1
    nums1 = [3, 1, 4, 2]
    p1 = 6
    print(minSubarray(nums1, p1))   # 输出: 1
    
    # 示例 2
    nums2 = [6, 3, 5, 2]
    p2 = 9
    print(minSubarray(nums2, p2))   # 输出: 2
    
    # 示例 3
    nums3 = [1, 2, 3]
    p3 = 3
    print(minSubarray(nums3, p3))   # 输出: 0