from typing import List

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        # 初始化答案数组全为 0。
        # 这样遍历结束后，栈内剩下的元素（找不到下一个更高温度的）天然就是 0，不需要额外清算
        ans = [0] * n 
        stack = []
        
        for i in range(n):
            # 当栈不为空，且当前遍历到的温度严格大于栈顶索引对应的温度时
            while stack and temperatures[stack[-1]] < temperatures[i]:
                cur = stack.pop()
                # 计算相差的天数
                ans[cur] = i - cur
            
            # 相等或小于的情况，以及栈为空的情况，都直接入栈索引
            stack.append(i)
            
        return ans  