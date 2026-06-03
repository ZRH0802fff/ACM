n=int(input())
tx=0
for x in range(1,101):
    if (n-52*7*x)%(52*21)==0:
        k=(n-52*7*x)/(52*21)
        if(k<=0):
            break
        tx=x
print(tx)
if k==0:
    print(1)
else:
    print(int(k))