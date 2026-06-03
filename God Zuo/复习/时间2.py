from datetime import datetime

# 输入 12:00:00 和 14:30:05
t1 = datetime.strptime(input(), "%H:%M:%S")
t2 = datetime.strptime(input(), "%H:%M:%S")

# 相减得到 timedelta 对象
delta = t2 - t1

# 获取总秒数差值（绝对值）
total_seconds = abs(int(delta.total_seconds()))
print(f"相差总秒数: {total_seconds}")

# 如果要看具体差了多少时分秒
print(f"时间差对象为: {delta}")