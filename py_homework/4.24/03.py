import random
import math

a = []
for i in range(10):
    a.append(random.randint(1, 100))

b = []
for x in a:
    b.append(round(math.sqrt(x), 2))

c = sum(b) / len(b)

print(a)
print(b)
print(c)