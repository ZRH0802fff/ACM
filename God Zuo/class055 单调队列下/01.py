class Solution:
    def shortestSubarray(self, nums: list[int], k: int) -> int:
        n = len(nums)
        
        # 1. 构建前缀和数组，长度为 n + 1
        # pref[i] 表示前 i 个元素的和
        pref = [0] * (n + 1)
        for i in range(n):
            pref[i + 1] = pref[i] + nums[i]
            
        # 2. 定长数组模拟双端队列，存放的是前缀和数组的【索引】
        q = [0] * (n + 1)
        h = 0
        t = 0
        
        ans = float('inf')
        
        for i in range(n + 1):
            # 逻辑 1：从队头结算（达标淘汰）
            # 如果 当前前缀和 - 队头前缀和 >= k，说明找到了一个有效子数组
            while h < t and pref[i] - pref[q[h]] >= k:
                length = i - q[h]
                if length < ans:
                    ans = length
                # 结算完直接弹出队头！
                # 因为如果后面还有 i' 也能和当前队头凑够 k，那它的长度 i' - q[h] 肯定比现在的长
                # 我们要求的是最短，所以队头毫无保留价值了
                h += 1
                
            # 逻辑 2：从队尾维护单调递增（变弱淘汰）
            # 如果队尾的前缀和 >= 当前的前缀和，队尾出队
            # 因为当前 i 的前缀和更小，意味着后面更容易凑出差值 >= k
            # 而且当前 i 的索引更大，凑出来的长度更短！
            # 队尾的元素在“潜力”和“距离”上被当前元素全面碾压，直接淘汰。
            while h < t and pref[q[t - 1]] >= pref[i]:
                t -= 1
                
            # 当前索引入队
            q[t] = i
            t += 1
            
        return ans if ans != float('inf') else -1