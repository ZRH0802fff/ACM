sn=input()
n=sn.replace('-','')
f=0
for i in range(9):
     f+=int(n[i])*(i+1)
s=f%11
if s==int(n[9]) or (s==10 and n[9]=='X'):
    print("Right")
else :
    print(sn[:-1]+str(s))