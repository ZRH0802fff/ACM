import sys

data = sys.stdin.read().split()
idx = 0

def gi():
    global idx
    val = int(data[idx])
    idx += 1
    return val

# 只要还有数据就继续读
while idx < len(data):
    n = gi()
    m = gi()
    
    mat_sum = 0
    for i in range(n):
        for j in range(m):
            mat_sum += gi()
    
    print(mat_sum)

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