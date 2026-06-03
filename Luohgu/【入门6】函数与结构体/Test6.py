n = int(input())

size = 1 << n
arr = [[0] * (size + 1) for _ in range(size + 1)]

def f(x, y, lev):
    if lev == 0:
        return
    t = 1 << (lev - 1)
    for i in range(x, x + t):
        for j in range(y, y + t):
            arr[i][j] = 0
        for j in range(y + t, y + 2 * t):
            arr[i][j] = 1
    for i in range(x + t, x + 2 * t):
        for j in range(y, y + 2 * t):
            arr[i][j] = 1
    f(x, y + t, lev - 1)
    f(x + t, y, lev - 1)
    f(x + t, y + t, lev - 1)

f(1, 1, n)

for i in range(1, size + 1):
    for j in range(1, size + 1):
        print(arr[i][j], end=' ')
    print()