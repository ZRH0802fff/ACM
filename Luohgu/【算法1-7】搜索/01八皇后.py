n=int(input())
col=[False]*n
d1=[False]*(2*n)
d2=[False]*(2*n)
path=[0]*n
tal=0

def dfs(r):
    global tal
    if r==n:
        tal+=1
        if tal<=3:
            print(' '.join(str(path[i]+1) for i in range(n)))
        return
    for c in range(n):
        if col[c] or d1[r-c+n] or d2[r+c]:
            continue
        path[r]=c

        col[c] = d1[r - c + n] = d2[r + c] = True
        dfs(r + 1)
        col[c] = d1[r - c + n] = d2[r + c] = False

dfs(0)
print(tal)