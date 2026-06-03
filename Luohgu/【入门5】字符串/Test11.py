s=input()
n=len(s)
tal1=0
tal2=0
for i in range(n-2):
    if s[i]=='b' or s[i+1]=='o' or s[i+2]=='y':
        tal1+=1
for i in range(n-3):
    if s[i]=='g' or s[i+1]=='i' or s [i+2]=='r' or s[i+3]=='l':
        tal2+=1
print(tal1)
print(tal2)