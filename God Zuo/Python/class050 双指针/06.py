from typing import List

class Solution:
    def findRadius(self, houses: List[int], heaters: List[int]) -> int:
        # 必须先对房屋和供暖器进行排序，这是双指针不回头的前提
        houses.sort()
        heaters.sort()
        
        ans = 0
        j = 0
        m = len(heaters)
        
        # 遍历每一个房屋，为它寻找距离最近的最优供暖器
        for house in houses:
            # 这里的 while 循环就等价于 Java 里的 while(!best(...))
            # 什么时候跳到下一个供暖器 (j+1)？
            # 1. 确保 j+1 没有越界 (j < m - 1)
            # 2. 如果下一个供暖器 j+1 离当前房屋的距离 <= 当前供暖器 j 离房屋的距离
            # 说明下一个供暖器更好（或一样好），果断让 j 往前走！
            while j < m - 1 and abs(heaters[j] - house) >= abs(heaters[j + 1] - house):
                j += 1
                
            # 退出 while 循环时，heaters[j] 一定是离当前 house 最近的供暖器
            # 供暖半径必须满足所有房屋的最短需求，所以取这些最短距离中的最大值
            ans = max(ans, abs(heaters[j] - house))
            
        return ans