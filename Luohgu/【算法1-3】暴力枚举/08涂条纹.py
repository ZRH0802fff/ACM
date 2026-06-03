import sys
data=sys.stdin.read().split()
n,m=int(data[0]),int(data[1])
idx=2
griph=['']*n
min_ans=float('inf')
for i in range(n):
    griph[i]=data[idx]
    idx+=1
for i in range(n-2):
    for j in range(n-1):
        ans=0
        for k in range(i+1):
            s=griph[k]
            for l in range(m):
                if s[l]!='W':
                    ans+=1
        for k in range(i+1,j+1):
            s=griph[k]
            for l in range(m):
                if s[l]!='B':
                    ans+=1
        for k in range(j+1,n):
            s=griph[k]
            for l in range(m):
                if s[l]!='R':
                    ans+=1
        if ans<min_ans:
            min_ans=ans
print(min_ans)
