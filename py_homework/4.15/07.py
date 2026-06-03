def conv2d(image, kernel):
    res = [[0, 0], [0, 0]]
    for i in range(2):
        for j in range(2):
            s = 0
            for m in range(3):
                for n in range(3):
                    s += image[i+m][j+n] * kernel[m][n]
            res[i][j] = s
    return res

image = [
    [10, 20, 30, 40],
    [50, 60, 70, 80],
    [90, 100, 110, 120],
    [130, 140, 150, 160]
]

kernel = [
    [-1, -1, -1],
    [-1,  8, -1],
    [-1, -1, -1]
]

output = conv2d(image, kernel)
print(output)