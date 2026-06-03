import sys

# 使用 sys.stdin.readline 替换 input()，速度更快
input = sys.stdin.readline

for line in sys.stdin:          # 或者写成 while (line := input()) is not None / != ''
    # 去除行尾换行符并按空格切分
    numbers = line.split()
    
    # 如果这一行是空的（只有换行），可以跳过（视题目而定，通常不需要）
    if not numbers:
        continue
    
    # 计算这一行的和
    total = sum(int(x) for x in numbers)
    
    # 直接输出
    print(total)