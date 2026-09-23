import sys
data=list(sys.stdin.read().split())
n=int(data[0])
idx=1
for i in range(n):
    s=int(data[idx])
    m=int(data[idx+1])
    t=data[idx+2]
    idx+=3
    tm=int(t[:2])*60+int(t[3:5])
    if m>=50 or m/s>=0.2 or tm>=240:
        print("YES")
    else:
        print("NO")