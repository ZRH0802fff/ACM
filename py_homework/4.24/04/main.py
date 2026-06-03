import losses

a = [0, 1, 0, 1]
b = [0.1, 0.9, 0.2, 0.8]

ans1 = losses.mse(a, b)
ans2 = losses.mae(a, b)
ans3 = losses.binary_cross_entropy(a, b)

print(ans1)
print(ans2)
print(ans3)