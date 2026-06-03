n1,n2,n3=map(int,input().split())
if n1==0:
    print("No!!!")
    exit()
ans=[]
for i in range(123,988):
    if (i*n2)%n1==0 and (i*n3)%n1==0:
        j=(i*n2)//n1
        k=(i*n3)//n1
        if j<1000 and k<1000:
            s = str(i) + str(j) + str(k)
            if len(s)==9 and '0' not in s and len(set(s))==9:
                ans.append(f"{i} {j} {k}")
if ans !=[]:
    for _ in ans:
        print(_)
else:
    print('No!!!')