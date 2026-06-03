n=int(input())
arr=list(map(int ,input().split()))
ff=[0]
for i in range(n):
    t=0
    if i==0:
        continue
    for j in range(i):
        if arr[i]>arr[j]:
            t+=1
    ff.append(t)
fff=''
for i in ff:
    fff=fff+str(i)+" "
print(fff)