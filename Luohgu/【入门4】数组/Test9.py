book=[
     # 0
    ["XXX", "X.X", "X.X", "X.X", "XXX"],
    # 1
    ["..X", "..X", "..X", "..X", "..X"],
    # 2
    ["XXX", "..X", "XXX", "X..", "XXX"],
    # 3
    ["XXX", "..X", "XXX", "..X", "XXX"],
    # 4
    ["X.X", "X.X", "XXX", "..X", "..X"],
    # 5
    ["XXX", "X..", "XXX", "..X", "XXX"],
    # 6
    ["XXX", "X..", "XXX", "X.X", "XXX"],
    # 7
    ["XXX", "..X", "..X", "..X", "..X"],
    # 8
    ["XXX", "X.X", "XXX", "X.X", "XXX"],
    # 9
    ["XXX", "X.X", "XXX", "..X", "XXX"]
]
n=int(input())
num=input().strip()
out=['' for _ in range(5)]
for i in range(5):
    for s in num:
        idx=ord(s)-ord('0')
        out[i]+=book[idx][i]+"."
    out[i]=out[i][:-1]
print("\n".join(out))