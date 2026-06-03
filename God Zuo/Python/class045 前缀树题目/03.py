from typing import List


class Solution:
    MAXN = 10001
    tree = [[0] * 26 for _ in range(MAXN)]
    pass_ = [0] * MAXN
    end = [None] * MAXN
    cnt = 0

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        if not board or not board[0]:
            return []
        self.build(words)
        ans = []
        for i in range(len(board)):
            for j in range(len(board[0])):
                self.dfs(board, i, j, 1, ans)
        self.clear()
        return ans

    def dfs(self, board: List[List[str]], i: int, j: int, t: int, ans: List[str]) -> int:
        # 越界或者走了回头路
        if i < 0 or i == len(board) or j < 0 or j == len(board[0]) or board[i][j] == "0":
            return 0
        # 不越界且不是回头路
        tmp = board[i][j]
        road = ord(tmp) - ord("a")
        t = self.tree[t][road]
        if self.pass_[t] == 0:
            return 0
        # i,j位置有必要来
        fix = 0
        if self.end[t] is not None:
            fix += 1
            ans.append(self.end[t])
            self.end[t] = None
        # 把i,j位置的字符改成"0"，后续过程不能再来到i,j位置
        board[i][j] = "0"
        fix += self.dfs(board, i - 1, j, t, ans)
        fix += self.dfs(board, i + 1, j, t, ans)
        fix += self.dfs(board, i, j - 1, t, ans)
        fix += self.dfs(board, i, j + 1, t, ans)
        self.pass_[t] -= fix
        board[i][j] = tmp
        return fix

    def build(self, words: List[str]) -> None:
        self.cnt = 1
        for word in words:
            cur = 1
            self.pass_[cur] += 1
            for char in word:
                path = ord(char) - ord("a")
                if self.tree[cur][path] == 0:
                    self.cnt += 1
                    self.tree[cur][path] = self.cnt
                cur = self.tree[cur][path]
                self.pass_[cur] += 1
            self.end[cur] = word

    def clear(self) -> None:
        for i in range(1, self.cnt + 1):
            for j in range(26):
                self.tree[i][j] = 0
            self.pass_[i] = 0
            self.end[i] = None