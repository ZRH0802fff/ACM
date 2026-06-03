a,b,c,d=map(float,input().split())
l,r=-10000,10000
out=[]
for num in range(-10000,10001):
    num/=100
    if a*num*num*num + b*num*num + c*num + d ==0:
        out.append(num)
print(' '.join(f"{x:.2f}" for x in out ))
