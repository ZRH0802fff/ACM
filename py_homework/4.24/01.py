import math


def sigmoid(x):
    if x >= 0:
        return 1 / (1 + math.exp(-x))
    else:
        return math.exp(x) / (1 + math.exp(x))
ans1 = sigmoid(0)
print(ans1)

def binary_cross_entropy(y_true, y_pred):
    e = 1e-7
    if y_pred < e:
        y_pred = e
    if y_pred > 1 - e:
        y_pred = 1 - e
    loss = -(y_true * math.log(y_pred) + (1 - y_true) * math.log(1 - y_pred))
    return loss

ans2 = binary_cross_entropy(1, 0.9)
print(ans2)