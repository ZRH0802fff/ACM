import math

def validate_input(func):
    def wrapper(x):
        if x < 0 or x > 1:
            print("警告：x不在[0, 1]范围内，进行裁剪")
            x = max(0, min(x, 1))
        return func(x)
    return wrapper

@validate_input
def activation(x):
    return 1 / (1 + math.exp(-x))

ans1 = activation(1.5)
ans2 = activation(0.2)

print(ans1)
print(ans2)