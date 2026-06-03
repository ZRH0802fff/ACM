# 测试链接 : https://www.nowcoder.com/practice/7037a3d57bbd4336856b8e16a9cafd71
import sys
data=iter(sys.stdin.read().split())
while True:
    n=next(data,None)
    if not n :
        break
    n=int(n)
    arr=[]
    max_val=0
    for _ in range(n):
        tm=int(next(data))
        arr.append(tm)
        if tm>max_val:
            max_val=tm
    l,r,ans=0,max_val,0
    def f (eng):
        for h in arr:
            eng=eng*2-h
            if eng>max_val:
                return True
            if eng<0:
                return False
        return True
    while l<=r:
        m=(l+r)//2
        if f(m):
            ans=m
            r=m-1
        else:
            l=m+1
    print(ans)