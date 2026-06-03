from typing import List

class Solution:
    def subarraysWithKDistinct(self, nums: List[int], k: int) -> int:
        
        # 内部辅助函数：计算数组中，不同整数个数「最多为 k」的子数组数量
        def atMostK(k: int) -> int:
            # 题目条件：1 <= nums[i] <= nums.length
            # 直接开辟一个大小为 n+1 的数组做词频统计，比字典更快
            n = len(nums)
            cnts = [0] * (n + 1)
            
            ans = 0
            l = 0
            collect = 0  # 收集到的不同数字的种类数
            
            for r in range(n):
                # 进窗口：如果是第一次遇到这个数字，种类数 +1
                if cnts[nums[r]] == 0:
                    collect += 1
                cnts[nums[r]] += 1
                
                # 收缩窗口：如果窗口内种类数超过了 k，左指针必须向右移动
                while collect > k:
                    cnts[nums[l]] -= 1
                    # 如果某个数字被完全移出窗口，种类数 -1
                    if cnts[nums[l]] == 0:
                        collect -= 1
                    l += 1
                
                # 关键点：当窗口合法时，以 r 结尾的合法子数组数量刚好是 r - l + 1
                ans += r - l + 1
                
            return ans

        # 核心数学转换：恰好为 K = 最多为 K - 最多为 K-1
        return atMostK(k) - atMostK(k - 1)