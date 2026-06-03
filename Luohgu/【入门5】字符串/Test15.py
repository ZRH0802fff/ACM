s=input().strip(';').split(';')
book={'a':0,'b':0,'c':0}
s = [stmt.strip() for stmt in s if stmt.strip()]
for c in s:
    name,va=c.split(':=')
    if va.isdigit():
        value=int(va)
    else:
        value=book[va]
    book[name]=value
print(f"{book['a']} {book['b']} {book['c']}")