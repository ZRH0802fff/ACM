n=int(input())
book=[]
for i in range(n):
    t=list(input().split())
    book.append(t)
for i in range(n):
    if len(book[i])==2:
        book[i].insert(0,'n')

def f(flag):
    if flag=='a':
        t=int(i[1])+int(i[2])
        s=i[1]+'+'+i[2]+'='+str(t)
        print(s)
        print(len(s))
    elif flag=='b':
        t=int(i[1])-int(i[2])
        s=i[1]+'-'+i[2]+'='+str(t)
        print(s)
        print(len(s))
    elif flag=='c':
        t=int(i[1])*int(i[2])
        s=i[1]+'*'+i[2]+'='+str(t)
        print(s)
        print(len(s))

ls=' '
for i in book:
    if i[0]!='n':
        f(i[0])
        ls=i[0]
    else:
        f(ls)