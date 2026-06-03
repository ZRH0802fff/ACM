a = [1.0, 2.0, 3.0]
b = [0.1, -0.2, 0.05]
c = 0.01

print("更新前:", a)


new = [p - c * g for p, g in zip(a, b)]

print("更新后:", new)