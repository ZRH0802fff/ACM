import os
import sys
ans=0
x=int(input())
for y in range(1,x+1):
  t=x|y
  if x+y>t and x+t>y and t+y>x:
    ans+=1
print(ans)