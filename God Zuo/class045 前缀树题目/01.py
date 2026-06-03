# 牛牛和他的朋友们约定了一套接头密匙系统，用于确认彼此身份
# 密匙由一组数字序列表示，两个密匙被认为是一致的，如果满足以下条件：
# 密匙 b 的长度不超过密匙 a 的长度。
# 对于任意 0 <= i < length(b)，有b[i+1] - b[i] == a[i+1] - a[i]
# 现在给定了m个密匙 b 的数组，以及n个密匙 a 的数组
# 请你返回一个长度为 m 的结果数组 ans，表示每个密匙b都有多少一致的密匙
# 数组 a 和数组 b 中的元素个数均不超过 10^5
# 1 <= m, n <= 1000
# 测试链接 : https://www.nowcoder.com/practice/c552d3b4dfda49ccb883a6371d9a6932

MAXN = 2000001
tree = [[0] * 12 for _ in range(MAXN)]
pass_ = [0] * MAXN
cnt = 0


def build():
    global cnt
    cnt = 1


# '0' ~ '9' 10个 0~9
# '#' 10
# '-' 11
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
    for i in range(1, cnt + 1):
        for j in range(12):
            tree[i][j] = 0
        pass_[i] = 0


def countConsistentKeys(b, a):
    build()
    # [3,6,50,10] -> "3#44#-40#"
    for nums in a:
        builder = []
        for i in range(1, len(nums)):
            builder.append(str(nums[i] - nums[i - 1]) + '#')
        insert(''.join(builder))
    ans = [0] * len(b)
    for i in range(len(b)):
        nums = b[i]
        builder = []
        for j in range(1, len(nums)):
            builder.append(str(nums[j] - nums[j - 1]) + '#')
        ans[i] = count(''.join(builder))
    clear()
    return ans