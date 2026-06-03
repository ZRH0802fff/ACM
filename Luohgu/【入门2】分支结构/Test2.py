import math

a,b,c=map(int ,input().split())
if b==0:
    print (0)
else:
    t=math.ceil(c/b)
    if t>a:
        t=a
    print(a-t)