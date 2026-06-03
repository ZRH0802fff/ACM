sn = input()
n = sn.replace('-', '')   # 把全部 '-' 去掉，得到 10 位字符串
f = 0
for i in range(9):        # 只取前 9 位算加权和
    f += int(n[i]) * (i + 1)  # 乘 1~9，不是 0~8
s = f % 11
s = 'X' if s == 10 else str(s)  # 余 10 对应 X
if s == n[9]:             # 第 10 位是识别码
    print("Right")
else:
    print(sn[:-1] + s)    # 把原串最后一位换成正确的