set_a = {1, 2, 3, 4, 5, 6}
set_b = {4, 5, 6, 7, 8, 9}
print("并集:", set_a | set_b)
print("交集:", set_a & set_b)
print("差集 (a - b):", set_a - set_b)
print("对称差:", set_a ^ set_b)
print("set_a 是否是 set_b 的子集:",set_a.issubset(set_b))