#测试链接 : https://www.luogu.com.cn/problem/P3397
import sys
data=sys.stdin.read().split()
ddx=iter(data)
try:
    while True:
        n=int(next(ddx))
        m=int(next(ddx))
        book=[[0]*(n+2) for _ in range(n+2)]
        for _ in range(m):
            a=int(next(ddx))
            b=int(next(ddx))
            c=int(next(ddx))
            d=int(next(ddx))
            book[a][b]+=1
            book[c+1][b]-=1
            book[a][d+1]-=1
            book[c+1][d+1]+=1
        ans=[]
        for i in range(1,n+1):
            for j in range(1,n+1):
                book[i][j]+=book[i-1][j]+book[i][j-1]-book[i-1][j-1]
            print(' '.join(map(str, book[i][1:n+1])))
except StopIteration:
    pass
