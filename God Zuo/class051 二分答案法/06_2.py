from typing import List

class Solution:
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        
        # 内部辅助函数：在给定的 time_limit 时间内，所有公交车一共能跑完多少趟？
        def count_trips(time_limit: int) -> int:
            # 【区别 1】：这里不需要 + 1
            # 课上的“等位问题”中，0 时刻可以直接接待一波客人。
            # 而这里的“旅途问题”，必须实打实地跑完 num 分钟才算完成 1 趟！
            return sum(time_limit // t for t in time)

        # 找到跑得最快的那辆公交车
        min_time = min(time)
        
        # 二分查找的范围设置
        l = 0
        # 最差情况：只让最快的那辆车一个人跑完所有的 totalTrips 趟
        r = min_time * totalTrips 
        ans = 0
        
        while l <= r:
            m = (l + r) // 2
            
            # 【区别 2】：这里的判断条件是 >= totalTrips，而不是 w + 1
            # 因为题目直接问的是“完成 totalTrips 趟”，不需要像排队那样算“你是第 w+1 个”
            if count_trips(m) >= totalTrips:
                # 能够在 m 时间内完成，记录答案，并尝试寻找更短的时间
                ans = m
                r = m - 1
            else:
                # 趟数不够，只能延长时间
                l = m + 1
                
        return ans