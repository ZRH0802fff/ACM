n=input()
n=int(n)
a1=0
a2=0
if n%2==0:
    a1=1
if n>4 and n<=12:
    a2=1
if a1+a2==2:
    print(1,end=" ")
else:
    print(0,end=" ")
if a1+a2>=1:
    print(1,end=" ")
else:
    print(0,end=" ")
if a1+a2==1:
    print(1,end=" ")
else:
    print(0,end=" ")
if a1+a2==0:
    print(1,end=" ")
else:
    print(0,end=" ")