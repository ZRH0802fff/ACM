n =int(input())
bk=[]

def f(i):
    return bk[i][3]>=800 and (bk[i][1]+bk[i][2])>140

for _ in range(n):
    t=list(map(int, input().split()))
    sum=t[1]*7+t[2]*8
    t.append(sum)
    bk.append(t)
for _ in range(n):
    if f(_):
        print('Excellent')
    else :
        print('Not excellent')