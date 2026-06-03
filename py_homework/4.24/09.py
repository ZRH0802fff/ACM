from functools import reduce

a = [0.1, 0.5, 0.8, 0.3, 0.9]

b = list(map(lambda x: 1 if x > 0.5 else 0, a))

c = list(filter(lambda x: x > 0.5, a))

d = reduce(lambda x, y: x * y, c)

print(b)
print(c)
print(d)