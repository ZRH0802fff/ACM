from typing import List

class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        n = len(gas)
        l = 0  # 窗口左边界（尝试的起点）
        
        # l 是尝试出发的起点，如果 l 越界了还没找到，说明跑不完一圈
        while l < n:
            r = l  # r 是当前能到达的最远位置
            current_sum = 0  # 当前油箱余量
            
            # 只要当前的油量加上下一个站的结余 >= 0，说明还能继续往下开
            while current_sum + gas[r % n] - cost[r % n] >= 0:
                # 检查是否已经转满了一圈
                if r - l + 1 == n:
                    return l
                
                # 把当前站的油量结余加进油箱
                current_sum += gas[r % n] - cost[r % n]
                # 继续向右探索下一个站
                r += 1
                
            # 核心优化（贪心）：
            # 如果从 l 出发最远只能到达 r（开不到 r+1）
            # 那么从 l 到 r 之间的任何一个点出发，都不可能开过 r！
            # 所以下一个尝试的起点直接跳到 r + 1，这就是为什么能做到 O(N) 的关键。
            l = r + 1
            
        return -1