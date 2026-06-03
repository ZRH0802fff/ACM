from typing import List

MAXN = 2000001
tree = [[0] * 12 for _ in range(MAXN)]
pass_ = [0] * MAXN
cnt = 0


def build():
    global cnt
    cnt = 1


def path(cha):
    if cha == '#':
        return 10
    elif cha == '-':
        return 11
    else:
        return ord(cha) - ord('0')


def insert(word):
    global cnt
    cur = 1
    pass_[cur] += 1
    for i in range(len(word)):
        p = path(word[i])
        if tree[cur][p] == 0:
            cnt += 1
            tree[cur][p] = cnt
        cur = tree[cur][p]
        pass_[cur] += 1


def count(pre):
    cur = 1
    for i in range(len(pre)):
        p = path(pre[i])
        if tree[cur][p] == 0:
            return 0
        cur = tree[cur][p]
    return pass_[cur]


def clear():
    global cnt
    for i in range(1, cnt + 1):
        for j in range(12):
            tree[i][j] = 0
        pass_[i] = 0


class Solution:
    def countConsistentKeys(self , b: List[List[int]], a: List[List[int]]) -> List[int]:
        build()
        # 将所有 a 的差值序列插入 Trie
        for nums in a:
            builder = []
            for i in range(1, len(nums)):
                builder.append(str(nums[i] - nums[i - 1]) + '#')
            insert(''.join(builder))
        
        ans = [0] * len(b)
        # 对每个 b 查询匹配的前缀数量
        for i in range(len(b)):
            nums = b[i]
            builder = []
            for j in range(1, len(nums)):
                builder.append(str(nums[j] - nums[j - 1]) + '#')
            ans[i] = count(''.join(builder))
        
        clear()
        return ans