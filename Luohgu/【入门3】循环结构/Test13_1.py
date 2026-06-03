n = int(input())
if n == 0:
    print("0.00")
else:
    a, b = 0, 1          # a=F(0), b=F(1)
    for _ in range(2, n+1):
        a, b = b, a+b
    print(f"{b:.2f}")