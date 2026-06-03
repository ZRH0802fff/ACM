# Python 版本

class Number:
    def __init__(self, v):
        self.val = v

def f(a):          # 基本类型（不可变对象）
    a = 0

def g1(b):         # 试图让外部变量指向别的对象
    b = None       # ← 在 Python 里这一行真的会生效！

def g2(b):         # 修改对象内部
    b.val = 6

def g3(c):         # 试图让 list 指向别的对象
    c = None

def g4(c):         # 修改 list 内部内容
    c[0] = 100


# 测试
a = 10
f(a)
print(a)           # 10          ← 不变（不可变对象）

b = Number(5)
g1(b)
print(b.val if b else "None")   # 5           ← Python 里这一行真的没改指向！？ 等下看解释

b = Number(5)
g2(b)
print(b.val)       # 6           ← 改内部成功

c = [1, 2, 3, 4]
g3(c)
print(c)           # [1, 2, 3, 4]  ← 没变成 None

c = [1, 2, 3, 4]
g4(c)
print(c)           # [100, 2, 3, 4] ← 改内部成功


# 链表反转（迭代版）几乎一模一样
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next   

def reverse_list(head):
    pre = None
    while head:
        nxt = head.next          # 暂存下一个
        head.next = pre          # 反指
        pre = head               # pre 前进
        head = nxt               # head 前进
    return pre