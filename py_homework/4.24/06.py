a = [-5, 3, -2, 7, 0, 10]

b = list(filter(lambda x: x > 0, a))

c = list(map(lambda x: (x - 1) / 9, b))

print(c)