class Solution:
    def findMaxValueOfEquation(self, points: list[list[int]], k: int) -> int:
        n = len(points)
        
        # 使用定长数组模拟双端队列
        # 队列中存放元组: (x_i, y_i - x_i)
        # 这样能最大化压榨运行时间，避免高频的二维数组寻址操作
        q = [(0, 0)] * n
        h = t = 0
        ans = -float('inf')

        # 直接在 for 循环中解包，速度快于 x = points[i][0]
        for x, y in points:
            
            # 1. 淘汰队头过期元素 (窗口左边界收缩)
            # 如果队头的 x_i 与当前的 x_j 距离超过 k，则队头失效
            while h < t and q[h][0] + k < x:
                h += 1
                
            # 2. 收集最大值答案
            # 经过上面的淘汰，如果队列还有元素，队头必定是合法且 (y_i - x_i) 最大的
            if h < t:
                # cur = (x_j + y_j) + (y_i - x_i)
                cur = x + y + q[h][1]
                if cur > ans:
                    ans = cur
                    
            # 3. 维护队尾单调递减 (新老元素优胜劣汰)
            # 我们需要维护的是 (y_i - x_i) 的严格递减队列
            diff = y - x
            while h < t and q[t - 1][1] <= diff:
                t -= 1
                
            # 4. 当前点入队
            q[t] = (x, diff)
            t += 1
            
        return ans