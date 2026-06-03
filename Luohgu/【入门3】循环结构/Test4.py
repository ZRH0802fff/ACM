n=int(input())
index=1
for i in range(n):
    line=""
    for j in range(n-i):
        line+=f"{index:02d}"
        index+=1
    print(line)