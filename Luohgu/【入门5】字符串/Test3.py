import math

s=input()
book=[0 for i in range(26)]

def isPrem(num):
    if num<=1:
        return False
    if num==2:
        return True
    if num%2==0:
        return False
    for i in range(3,int(math.sqrt(num)),2):
        if num%i==0:
            return False
    return True

for c in s:
    t=ord(c.lower())-ord('a')
    book[t]+=1

ms=set(book)
ms.remove(0)
t=max(ms)-min(ms)
if isPrem(t):
    print("Lucky Word")
    print(t)
else:
    print("No Answer")
    print(0)