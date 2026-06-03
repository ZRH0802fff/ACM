# 用固定数组实现前缀树，空间使用是静态的。推荐！
# 测试链接 : https://www.nowcoder.com/practice/7f8a8553ddbf4eaab749ec988726702b
# 请同学们务必参考如下代码中关于输入、输出的处理
# 这是输入输出处理效率很高的写法
# 提交以下的code，可以直接通过（Python无需改类名）

import sys

MAXN = 150001
tree = [[0] * 26 for _ in range(MAXN)]
end_ = [0] * MAXN
pass_ = [0] * MAXN
cnt = 0


def build():
    global cnt
    cnt = 1


def insert(word):
    global cnt
    cur = 1
    pass_[cur] += 1
    for i in range(len(word)):
        path = ord(word[i]) - ord('a')
        if tree[cur][path] == 0:
            cnt += 1
            tree[cur][path] = cnt
        cur = tree[cur][path]
        pass_[cur] += 1
    end_[cur] += 1


def search(word):
    cur = 1
    for i in range(len(word)):
        path = ord(word[i]) - ord('a')
        if tree[cur][path] == 0:
            return 0
        cur = tree[cur][path]
    return end_[cur]


def prefixNumber(pre):
    cur = 1
    for i in range(len(pre)):
        path = ord(pre[i]) - ord('a')
        if tree[cur][path] == 0:
            return 0
        cur = tree[cur][path]
    return pass_[cur]


def delete(word):
    if search(word) > 0:
        cur = 1
        pass_[cur] -= 1
        for i in range(len(word)):
            path = ord(word[i]) - ord('a')
            pass_[tree[cur][path]] -= 1
            if pass_[tree[cur][path]] == 0:
                tree[cur][path] = 0
                return
            cur = tree[cur][path]
        end_[cur] -= 1


def clear():
    for i in range(1, cnt + 1):
        for j in range(26):
            tree[i][j] = 0
        end_[i] = 0
        pass_[i] = 0


# 高效输入处理（与Java BufferedReader思路完全一致）
data = sys.stdin.read().split()
idx = 0
while idx < len(data):
    build()
    m = int(data[idx])
    idx += 1
    for _ in range(m):
        op = int(data[idx])
        idx += 1
        word = data[idx]
        idx += 1
        if op == 1:
            insert(word)
        elif op == 2:
            delete(word)
        elif op == 3:
            print("YES" if search(word) > 0 else "NO")
        elif op == 4:
            print(prefixNumber(word))
    clear()