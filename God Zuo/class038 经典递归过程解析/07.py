# 打印 n 层汉诺塔问题的最优移动轨迹

def hanoi(n):
    if n > 0:
        f(n, "左", "右", "中")


def f(i, from_, to, other):
    if i == 1:
        print(f"移动圆盘 1 从 {from_} 到 {to}")
    else:
        f(i - 1, from_, other, to)
        print(f"移动圆盘 {i} 从 {from_} 到 {to}")
        f(i - 1, other, to, from_)


# 测试代码
if __name__ == "__main__":
    n = 3
    hanoi(n)