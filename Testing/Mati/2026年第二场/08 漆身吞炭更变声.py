import sys
data=list(map(int,sys.stdin.read().split()))
n=data[0]
ans=0
for i in range(1,n+1):
    s=bin(data[i])[2:]
    if len(s)<8:
        s='0'*(8-len(s))+s
    s=s[4:]+s[:4]
    ans+=int(s,2)
print(ans)