import math
n = int(input())
sqrt5 = math.sqrt(5)
phi = (1 + sqrt5) / 2
psi = (1 - sqrt5) / 2
fn = (phi**n - psi**n) / sqrt5
print(f"{fn:.2f}")