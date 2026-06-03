from functools import cache

class Solution:
    # ==========================================
    # 方法一 & 方法二：暴力递归（按长度划分）
    # 在 Python 中，通常直接用长度来表示状态，避免越界讨论
    # ==========================================
    def longestCommonSubsequence1(self, text1: str, text2: str) -> int:
        def dfs(i: int, j: int) -> int:
            # 任何一个字符串前缀长度为0，公共子序列长度就是0
            if i == 0 or j == 0:
                return 0
            # 尾字符相等：各自剥离尾字符，加上当前的 1 个长度
            if text1[i - 1] == text2[j - 1]:
                return dfs(i - 1, j - 1) + 1
            # 尾字符不等：考察 text1 退一步 或 text2 退一步 的最大值
            return max(dfs(i - 1, j), dfs(i, j - 1))
            
        return dfs(len(text1), len(text2))

    # ==========================================
    # 方法三：记忆化搜索 (Pythonic 终极杀器)
    # ==========================================
    def longestCommonSubsequence3(self, text1: str, text2: str) -> int:
        # 💡 竞赛大招：直接使用内置的 @cache 装饰器
        # 它会在后台自动维护一个字典做备忘录，省去所有手动创建 dp 数组的繁琐步骤
        @cache
        def dfs(i: int, j: int) -> int:
            if i == 0 or j == 0:
                return 0
            if text1[i - 1] == text2[j - 1]:
                return dfs(i - 1, j - 1) + 1
            return max(dfs(i - 1, j), dfs(i, j - 1))
            
        ans = dfs(len(text1), len(text2))
        dfs.cache_clear() # 竞赛好习惯：如果涉及多组测试用例，记得清空缓存防 MLE
        return ans

    # ==========================================
    # 方法四：严格位置依赖的动态规划  
    # ==========================================
    def longestCommonSubsequence4(self, text1: str, text2: str) -> int:
        n, m = len(text1), len(text2)
        # 初始化 (n+1) x (m+1) 的二维数组，全为 0
        dp = [[0] * (m + 1) for _ in range(n + 1)]
        
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                if text1[i - 1] == text2[j - 1]:
                    # 依赖左上角的值
                    dp[i][j] = dp[i - 1][j - 1] + 1
                else:
                    # 依赖上方和左方的值
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
                    
        return dp[n][m]

    # ==========================================
    # 方法五：动态规划 + 空间压缩 (最优解)
    # ==========================================
    def longestCommonSubsequence5(self, text1: str, text2: str) -> int:
        # 优化点：让 text2 永远是较短的那个字符串，这样可以使 dp 数组最短
        if len(text1) < len(text2):
            text1, text2 = text2, text1 # Pythonic 的变量交换逻辑
            
        n, m = len(text1), len(text2)
        # 只需要一个长度为 m+1 的一维数组
        dp = [0] * (m + 1)
        
        for i in range(1, n + 1):
            # left_up 相当于未压缩前 dp[i-1][j-1] 的值
            left_up = 0
            for j in range(1, m + 1):
                # 覆盖前先备份当前位置的值，它将成为下一个元素的 left_up
                backup = dp[j] 
                
                if text1[i - 1] == text2[j - 1]:
                    dp[j] = left_up + 1
                else:
                    # dp[j] 是上方的值，dp[j-1] 是左方的值
                    dp[j] = max(dp[j], dp[j - 1])
                    
                left_up = backup
                
        return dp[m]