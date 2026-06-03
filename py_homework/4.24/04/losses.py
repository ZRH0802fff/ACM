import math

def mse(y_true, y_pred):
    return sum((t-p) ** 2 for t,p in zip(y_true,y_pred))/len(y_true)

def mae(y_true, y_pred):
    return sum(abs(t-p) for t,p in zip(y_true,y_pred))/len(y_true)

def binary_cross_entropy(y_true, y_pred):
    eps = 1e-15
    total = 0
    for t, p in zip(y_true, y_pred):
        p = max(min(p, 1-eps), eps)
        total += -(t * math.log(p) + (1-t) * math.log(1-p))
    return total / len(y_true)