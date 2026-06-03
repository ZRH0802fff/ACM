import os
import sys
data= iter(sys.stdin.read().split())
while True:
    n=next(data,None)
    if n is None:
        break
    n=int(n)
    m=int(next(data))
    arr=[]
    larr=[[0]*1005 for i in range(2005)]
    rarr=[[0]*1005 for i in range(2005)]
    ans=0
    for i in range(n):
        for j in range(m):
            num=int(next(data))
            arr.append(num)
            ans+=larr[j-i][num]+rarr[i+j][num]
            larr[j-i][num]+=1
            rarr[i+j][num]+=1
    print(ans*2)
        

  
