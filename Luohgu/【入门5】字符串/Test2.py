n=int(input())
s=input()
f=''
for c in s:
    f+=chr((ord(c)-ord('a')+n)%26+ord('a'))
print(f)