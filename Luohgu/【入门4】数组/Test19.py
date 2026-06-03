f=input()
n=len(f)
for i in range(n-1):
    f+=input()
ans=str(n)
t=0
flag='0'
for i in f:
    if i==flag:
        t+=1
    else:
        ans+=" "+str(t)
        t=1
        if flag=='0':
            flag='1'
        else:
            flag='0'
ans+=" "+str(t)
print(ans)