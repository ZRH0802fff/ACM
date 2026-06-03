# num=14
# ans=''
# while num>0:
#     ans+=str(num%2)
#     num//=2
# print(ans[::-1])

# for num in range(1,15):
#     fnum=num
#     ans=''
#     while num>0:
#         ans+=str(num%2)
#         num//=2
#     print(fnum,ans[::-1])

book=['','2(0)','2','2+2(0)','2(2)','2(2)+2(0)','2(2)+2','2(2)+2+2(0)','2(2+2(0))','2(2+2(0))+2(0)','2(2+2(0))+2','2(2+2(0))+2+2(0)','2(2+2(0))+2(2)','2(2+2(0))+2(2)+2(0)','2(2+2(0))+2(2)+2']

n=int(input())
s=''
while n>0:
    s+=str(n%2)
    n//=2
s=s[::-1]
#print(s,len(s))
slen=len(s)
ans=''
for i in range(slen):
    if s[i]=='1':
        op=slen-i-1
        if op>2:
            ans+="2("+book[op]+")+"
            #print(f"op={op} 中上{ans}")
        elif op==2:
            ans+="2(2)+"
        elif op==1:
            ans+='2+'
        elif op==0:
            ans+='2(0)'
        else:
            ans+=book[op+1]+"+"
            #print(f"op={op} 中下{ans}")
idx=0
for i in range(len(ans)-1,-1,-1):
    if ans[i]!='+':
        idx=i
        break
print(ans[:idx+1])
