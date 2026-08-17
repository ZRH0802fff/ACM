from typing import List

def subarraySum(nums: List[int], aim: int) -> int:
    # key: 前缀和
    # value: 该前缀和出现的次数
    prefix_map = {0: 1}   # 重要：空数组的前缀和0出现1次
    
    ans = 0
    cur_sum = 0
    
    for num in nums:
        cur_sum += num
        
        # 查找是否有前缀和 = cur_sum - aim
        ans += prefix_map.get(cur_sum - aim, 0)
        
        # 更新当前前缀和的出现次数
        prefix_map[cur_sum] = prefix_map.get(cur_sum, 0) + 1
    
    return ans