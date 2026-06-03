k=int(input())
n=1
sn=0
for i in range(1,10000000):
    sn+=1/n
    if(sn>k):
        break
    else:
        n+=1
print(n)