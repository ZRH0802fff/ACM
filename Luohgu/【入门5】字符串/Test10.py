n=int(input())
s=input()
flag=-2
tal=0
p=1
for i in range(n-1):
    if s[i]=='V' and s[i+1]=='K':
        s=s[:i]+'XX'+s[i+1:]
        tal+=1
for i in range(n-1):
    if s[i]=='V'and s[i+1]=='V':
        tal+=1
        break
print(tal)