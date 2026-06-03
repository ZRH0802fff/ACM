import sys

n=int(input)
s=input()
for i in range(n):
    data=sys.stdin.readline().split()
    cz=int(data[0])
    if cz==1:
        s1=data[1]
        print(s.find(s1))
    elif cz==2:
        b1=data[1]
        b2=data[2]
        s=s.replace(b1,b2,1)
        print(s)
    else:
        c1=data[1]
        c2=data[2]
        c3=data[3]
        len1=len(c1)
        c=c1+c2
        s=s.replace(c,c1+c2+c3)
        print(s)

