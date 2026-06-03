from typing import List

class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        m, n = len(board), len(board[0])
        word_len = len(word)
        
        # 内部嵌套函数，直接捕获外部变量 m, n, board, word, word_len
        def dfs(i: int, j: int, k: int) -> bool:
            # 终止条件1：已经匹配完整个单词，成功找到
            if k == word_len:
                return True
            
            # 终止条件2：越界，或者当前字符不匹配
            if i < 0 or i == m or j < 0 or j == n or board[i][j] != word[k]:
                return False
            
            # 走到这里说明 board[i][j] == word[k]
            tmp = board[i][j]
            # 标记为已访问（比如用 '#'），防止走回头路
            board[i][j] = '#'
            
            # 向四个方向进行探索
            # Python 的 or 具有短路特性：只要有一个返回 True，后面的递归就不会执行
            ans = (dfs(i - 1, j, k + 1) or 
                   dfs(i + 1, j, k + 1) or 
                   dfs(i, j - 1, k + 1) or 
                   dfs(i, j + 1, k + 1))
            
            # 恢复现场（回溯）
            board[i][j] = tmp
            
            return ans

        # 遍历网格，寻找单词的起点
        for i in range(m):
            for j in range(n):
                # 只有当首字母匹配时才开始深搜（稍微剪枝）
                if board[i][j] == word[0] and dfs(i, j, 0):
                    return True
                    
        return False