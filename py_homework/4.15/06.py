import random

def train_model():
    a = round(random.uniform(0.1, 0.5), 4)
    b = round(random.uniform(0.8, 0.99), 2)
    c = random.randint(100, 500)
    return a, b, c

val1, val2, val3 = train_model()

print(val1)
print(val2)
print(val3)