import sys

# ─────────────── 一次性把所有输入全部读进来 ───────────────
data = sys.stdin.read().split()

# 全局指针，从 0 开始
idx = 0

# 辅助函数：每次调用就拿下一个整数
def gi():
    global idx
    val = int(data[idx])
    idx += 1
    return val

# ─────────────── 主逻辑 ───────────────
T = gi()           # 先读组数

for _ in range(T):
    n = gi()
    m = gi()
    
    # 读 n 行，每行 m 个数
    total = 0
    for i in range(n):
        for j in range(m):
            num = gi()
            total += num
    
    print(total)

# 3          ← 有3组测试数据
# 5 3        ← 第一组：n=5 m=3
# 1 2 3
# 4 5 6
# -1 -2 -3
# 7 8 9
# 0 0 0
# 2 2        ← 第二组：n=2 m=2
# 10 20
# 30 40
# 1 1        ← 第三组：n=1 m=1
# 999



#——————————比赛常用极简写法——————————
# import sys

# data = sys.stdin.read().split()
# i = 0

# while i < len(data):
#     n = int(data[i]); i += 1
#     m = int(data[i]); i += 1
    
#     s = 0
#     for _ in range(n * m):
#         s += int(data[i]); i += 1
    
#     print(s)