n,k=map(int,input().split())
arra=[]
arrb=[]
for i in range(n+1):
    if i==0:
        continue
    if i%k==0 :
        arra.append(i)
    else :
        arrb.append(i)
avga=0
avgb=0
for i in arra:
    avga+=i
for i in arrb:
    avgb+=i
avga/=len(arra)
avgb/=len(arrb)
print(f"{avga:.1f} {avgb:.1f}") 