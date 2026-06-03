book=[1,2,3,
      1,2,3,
      1,2,3,
      1,2,3,
      1,2,3,
      1,2,3,4,
      1,2,3,
      1,2,3,4]
s=input()
tal=0
for c in s :
    if c==' ':
        tal+=1
    else:
        idx=int(ord(c)-ord('a'))
        tal+=book[idx]
print(tal)