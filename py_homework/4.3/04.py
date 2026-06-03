a = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
b = [[9, 8, 7], [6, 5, 4], [3, 2, 1]]

c = [[a[i][j] + b[i][j] for j in range(3)] for i in range(3)]
print(c)

d = [[a[i][j] - b[i][j] for j in range(3)] for i in range(3)]
print(d)

e = [[sum(a[i][k] * b[k][j] for k in range(3)) for j in range(3)] for i in range(3)]
print(e)

f = sum(a[i][i] for i in range(3))
print(f)