s=input().replace(" ","")
book=[]
total=0
for c in s:
    if c not in book:
        total+=1
    else:
        book.append(c)
print(total)