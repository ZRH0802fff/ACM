import sys
data=list(map(int,sys.stdin.read().split()))
n=len(data)//3-1
idx=0
out=[]
memo=[[[0]*22 for _ in range(22)] for __ in range(22)]
for ___ in range(n):
    a,b,c=data[idx],data[idx+1],data[idx+2]
    idx+=3

    def w(a,b,c):
        if a<=0 or b<=0 or c<=0:
            return 1
        elif a>20 or b>20 or c>20:
            return w(20,20,20)
        elif memo[a][b][c]!=0:
            return memo[a][b][c]
        if a < b and b < c:
            memo[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c)
        else:
            memo[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1)
        return memo[a][b][c]
    t=w(a,b,c)
    out.append(f"w({a}, {b}, {c}) = {t}")
sys.stdout.write('\n'.join(s for s in out))