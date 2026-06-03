book=[' /\ ','/__\\']
n=int(input())
for i in range(2,n+1):
    kao=book[::1]
    jiakong=len(book[0])//2
    t=''
    for _ in range(jiakong):
        t+=' ' 
    for i in range(len(book)):
        book[i]=t+book[i]+t
    for l in kao:
        l+=l
        book.append(l)
for __ in book:
    print(__)