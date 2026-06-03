import math
x1,y1=map(int,input().split())
x2,y2=map(int,input().split())
x3,y3=map(int,input().split())
c1=math.sqrt((x2-x1)**2+(y2-y1)**2)
c2=math.sqrt((x3-x1)**2+(y3-y1)**2)
c3=math.sqrt((x2-x3)**2+(y2-y3)**2)
c=c1+c2+c3
print(f"{c:.2f}")