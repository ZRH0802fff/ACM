s=float(input())
t=2
total=0
while s>0:
    s-=t
    t*=0.98
    total+=1
print(total)