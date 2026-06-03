import sys
data=sys.stdin.read().split()
n,len=int(data[0]),int(data[1])
idx=2
book=[[0],False]*len
for _ in range(n):
    l=int(data[idx]);idx+=1
    s=int(data[idx]);idx+=1
    book[l][0]=s
