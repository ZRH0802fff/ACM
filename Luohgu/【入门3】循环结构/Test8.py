k=int(input())
sum=0
day=0
i=1
while day<k:
    for _ in range(i):
        day+=1
        sum+=i
        if day==k:
            break
    i+=1
print(sum)