s1=input()
s2=input()
n1,n2=1,1
for c in s1:
    n1*=ord(c)-ord('A')+1
for c in s2:
    n2*=ord(c)-ord('A')+1
n1%=47
n2%=47
if n1==n2:
    print('GO')
else:
    print('STAY')