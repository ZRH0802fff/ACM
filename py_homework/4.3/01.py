import numpy as np

v1 = np.array([2, 4, 6, 8])
v2 = np.array([1, 3, 5, 7])

v_add = v1 + v2
print(f"v1 + v2 = {v_add}")

v_sub = v1 - v2
print(f"v1 - v2 = {v_sub}")

v_dot = np.dot(v1, v2)
print(f"v1 与 v2 的点积 = {v_dot}")

v1_l2 = np.linalg.norm(v1)
print(f"v1 的 L2 范数 = {v1_l2:.4f}")