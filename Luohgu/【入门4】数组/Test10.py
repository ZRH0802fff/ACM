m, n = map(int, input().split())
cnt = [0] * 10
for x in range(m, n + 1):
    t = x
    while t!=0:
        cnt[t % 10] += 1
        t //= 10
print(' '.join(map(str, cnt)))