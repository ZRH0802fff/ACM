# 最低票价 (Minimum Cost For Tickets)
# 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/

DURATIONS = [1, 7, 30]

# ==========================================
# 1. 暴力尝试 (纯递归)
# ==========================================
def mincostTickets1(days: list[int], costs: list[int]) -> int:
    n = len(days)
    
    # days[i.....] 最少花费是多少
    def f1(i: int) -> int:
        if i == n:
            # 后续已经无旅行了
            return 0
            
        ans = float('inf')
        for k in range(3):
            j = i
            # 找到当前通行证无法覆盖的第一天
            while j < n and days[i] + DURATIONS[k] > days[j]:
                j += 1
            ans = min(ans, costs[k] + f1(j))
            
        return ans
        
    return f1(0)


# ==========================================
# 2. 暴力尝试改记忆化搜索 (自顶向下的动态规划)
# ==========================================
def mincostTickets2(days: list[int], costs: list[int]) -> int:
    n = len(days)
    # 初始化 dp 数组，用 float('inf') 表示未计算过
    dp = [float('inf')] * n
    
    def f2(i: int) -> int:
        if i == n:
            return 0
        # 如果已经计算过，直接返回缓存的值（剪枝）
        if dp[i] != float('inf'):
            return dp[i]
            
        ans = float('inf')
        for k in range(3):
            j = i
            while j < n and days[i] + DURATIONS[k] > days[j]:
                j += 1
            ans = min(ans, costs[k] + f2(j))
            
        # 记录答案
        dp[i] = ans
        return ans
        
    return f2(0)


# ==========================================
# 3. 严格位置依赖的动态规划 (自底向上的动态规划)
# ==========================================
def mincostTickets3(days: list[int], costs: list[int]) -> int:
    n = len(days)
    # dp[i] 表示从第 i 个旅行日开始到最后的最小花费
    dp = [float('inf')] * (n + 1)
    dp[n] = 0  # 对应递归中的 base case：i == n 时花费为 0
    
    # 从后往前遍历
    for i in range(n - 1, -1, -1): 
        for k in range(3):
            j = i
            while j < n and days[i] + DURATIONS[k] > days[j]:
                j += 1
            dp[i] = min(dp[i], costs[k] + dp[j])
            
    return dp[0]

# ==========================================
# 补充：更 Pythonic 的记忆化搜索 (使用 @cache)
# ==========================================
from functools import cache

def mincostTickets_pythonic(days: list[int], costs: list[int]) -> int:
    n = len(days)
    
    @cache  # 自动接管 dp 数组的缓存逻辑
    def f(i: int) -> int:
        if i == n:
            return 0
            
        ans = float('inf')
        for k in range(3):
            j = i
            while j < n and days[i] + DURATIONS[k] > days[j]:
                j += 1
            ans = min(ans, costs[k] + f(j))
            
        return ans
        
    return f(0)