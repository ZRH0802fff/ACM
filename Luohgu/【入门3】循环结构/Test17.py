n=int(input())
index=1
for i in range(n):
    t=""
    for j in range(n):
        t+=f"{index:02d}"
        index+=1
    print(t)
print()
index=1
for i in range(1,n+1):
    t=""
    for j in range(n-i):
        t+="  "
    for j in range(i):
        t+=f"{index:02d}"
        index+=1
    print(t)