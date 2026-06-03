n=int(input())
bk=[]
for i in range(n):
    t=input().split()
    bk.append(t)
summax=-1
for i in range(n) :
    sumt=int(bk[i][1])+int(bk[i][2])+int(bk[i][3])
    if sumt>summax:
        summax=sumt
        idx=i
f=' '.join(bk[idx])
print(f)