import os
import sys

data=sys.stdin.read().split()
n=int(data[0])
idx=1
for i in range(n):
  s=data[idx]
  idx+=1
  numo=numO=num0=0
  numB=numS=numN=0
  for ch in s:
    if 'a'<= ch <='z':
      numS+=1
      if ch=='o':
        numo+=1
    elif 'A'<=ch <= 'Z':
      numB+=1
      if ch=='O':
        numO+=1
    else:
      numN+=1
      if ch=='0':
        num0+=1
  if numB!=0 and numS!=0 and numN!=0:
    print(0)
    continue
  def f (xee,xer,Xee):
    # xee turn to xer
    if xee <1:
      return False
    if Xee==1:
      return False
    Xee-=1
    xee-=1
    xer+=1
    return True
  op=0
  if numB==0:
    if f(numo, numO,numS):
      numo-=1 
      numS-=1
      numO+=1
      op+=1
    elif f(num0,numO,numN):
      num0-=1
      numN-=1
      numO+=1
      op+=1
    else:
      print(-1)
      continue
  if numN==0:
    if f(numo,num0,numS) :
      numo-=1 
      numS-=1
      numN+=1
      op+=1
    elif f(numO,num0,numN):
      numO-=1
      numB-=1
      numN+=1
      op+=1
    else:
      print(-1)
      continue
  if numS==0:
    if f(numO,numo,numB):
      numO-=1
      numB-=1
      numS+=1
      op+=1
    elif f(num0,numo,numN):
        num0-=1
        numN-=1
        numS+=1
        op+=1
    else:
      print(-1)
      continue
  print(op)