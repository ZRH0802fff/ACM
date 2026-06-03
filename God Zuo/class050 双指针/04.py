from typing import List

class Solution:
    def numRescueBoats(self, people: List[int], limit: int) -> int:
        # 1. 对体重进行升序排序
        # 时间复杂度 O(N log N)
        people.sort()
        
        ans = 0
        l = 0
        r = len(people) - 1
        
        # 2. 双指针贪心匹配
        while l <= r:
            # 如果最轻的和最重的能一起坐下，左指针向内收缩（最轻的上船）
            if people[l] + people[r] <= limit:
                l += 1
                
            # 无论是否拼船成功，最重的那个人肯定都要单独或拼船走掉
            # 所以右指针永远会向内收缩，船的数量永远 +1
            r -= 1
            ans += 1
            
        return ans