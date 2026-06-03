s=''
for i in range(4):
    t=input().strip()
    s+=t
book=[0 for i in range(26)]
for c in s:
    if c>='A' and c<='Z':
        book[ord(c)-ord('A')]+=1
pr=["A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"]
mn=max(book)
for i in range(mn):
    t=''
    for i in range(26):
        if book[i]>0:
            t+='* '
            book[i]-=1
        else:
            t+='  '
    pr.append(t)
for c in pr[::-1]:
    print(c[:52])