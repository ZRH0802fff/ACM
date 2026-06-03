from collections import deque
n,m,x,y=map(int,input().split())
ans=[[-1]*m for _ in range(n)]

ans[x-1][y-1]=0
queue=deque([(x-1,y-1)])
dx = [-2, -2, -1, -1, 1, 1, 2, 2]
dy = [-1, 1, -2, 2, -2, 2, -1, 1]

while queue:
    cx,cy=queue.popleft()
    for i in range(8):
        nx,ny=cx+dx[i],cy+dy[i]
        if 0 <= nx < n and 0 <= ny < m:
            if ans[nx][ny]==-1:
                ans[nx][ny]=ans[cx][cy]+1
                queue.append((nx,ny))

for l in ans:
    print(*l)
