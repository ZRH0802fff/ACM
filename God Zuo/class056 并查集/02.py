import sys

# 【极其重要】省去小挂大优化后，必须手动扩充递归深度，防止洛谷 RE
sys.setrecursionlimit(300000)

# 1. 一次性读取所有数据，分割为字符串数组
input_data = sys.stdin.read().split()
if not input_data:
    sys.exit()

# 2. 使用 idx 游标手动控制读取位置
n = int(input_data[0])
m = int(input_data[1])
idx = 2

# 初始化 father 数组
father = list(range(n + 1))

# 极简版递归路径压缩
def find(i):
    if i != father[i]:
        father[i] = find(father[i])
    return father[i]

# 极简版合并
def union(x, y):
    father[find(x)] = find(y)

out = []

# 3. 循环处理 m 次查询，通过 idx 自增步进
for _ in range(m):
    z = int(input_data[idx])
    x = int(input_data[idx+1])
    y = int(input_data[idx+2])
    idx += 3  # 每次消耗 3 个数字，游标往前推
    
    if z == 1:
        union(x, y)
    else:
        out.append("Y" if find(x) == find(y) else "N")

# 4. 批量输出结果
sys.stdout.write('\n'.join(out) + '\n')