import math

fn=10000000000000
n=int(input())
for _ in range(3):
    num,money=map(int ,input().split())
    t=math.ceil(n/num)*money
    fn=min(fn,t)
print (fn)