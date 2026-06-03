import sys
from collections import Counter
data=list(map(int,sys.stdin.read().split()))
n,c=data[0],data[1]
book=Counter(data[2:])
setnum=set(data[2:])
ans=0
for b in setnum:
    a=b+c
    ans+=book[b]*book[a]
print(ans)