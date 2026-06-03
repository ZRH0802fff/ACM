from typing import List

class Solution:
    
    # =========================================================
    # 解法一：纯粹的二分答案法
    # 二分范围：[0, 电池总电量]
    # =========================================================
    def maxRunTime1(self, n: int, batteries: List[int]) -> int:
        
        # 内部辅助函数：检查给定的 time 分钟，能否让 n 台电脑跑满
        def check(time: int) -> bool:
            fragments = 0
            target_computers = n
            
            for x in batteries:
                if x > time:
                    # 如果这块电池容量比目标时间还要大，它完全可以自己独立承包一台电脑
                    target_computers -= 1
                else:
                    # 否则，把它当成“碎片电池”收集起来，用于拼凑供电
                    fragments += x
                    
                # 如果收集到的碎片电量，已经足够填满剩下的所有电脑了，直接达标！
                if fragments >= target_computers * time:
                    return True
                    
            return False

        # 二分查找
        l = 0
        r = sum(batteries)
        ans = 0
        
        while l <= r:
            m = (l + r) // 2
            if check(m):
                # 达标了！记录答案，并尝试能不能运行更长时间（去右侧找）
                ans = m
                l = m + 1
            else:
                # 撑不到 m 分钟，必须降低期望（去左侧找）
                r = m - 1
                
        return ans

    # =========================================================
    # 解法二（最优解）：二分答案法 + 贪心数学优化
    # 二分范围：[0, 单块电池的最大值]
    # =========================================================
    def maxRunTime(self, n: int, batteries: List[int]) -> int:
        total_sum = sum(batteries)
        max_bat = max(batteries)
        
        # 【核心贪心优化点】：
        # 如果总电量非常充裕，甚至超过了 "最大单块电池 * 电脑数"
        # 那么没有任何一块电池会因为“自己容量太大、其他电池拼凑不上”而发生电量浪费。
        # 此时所有的电池都可以视作完美的“碎片拼接”，直接取平均数就是最大运行时间！
        if total_sum > max_bat * n:
            return total_sum // n
            
        # 如果走到了这里，说明最终的供电时间一定不会超过 max_bat
        # 所以二分的右边界可以直接压缩到 max_bat，极大减少二分次数
        
        def check(time: int) -> bool:
            fragments = 0
            target_computers = n
            for x in batteries:
                if x > time:
                    target_computers -= 1
                else:
                    fragments += x
                if fragments >= target_computers * time:
                    return True
            return False

        l = 0
        r = max_bat
        ans = 0
        
        while l <= r:
            m = (l + r) // 2
            if check(m):
                ans = m
                l = m + 1
            else:
                r = m - 1
                
        return ans