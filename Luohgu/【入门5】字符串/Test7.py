n=int(input())
s=input().strip()
for _ in range(n):
    t=input().split()
    if t[0]=='1':
        s+=t[1]
        print(s)
    elif t[0]=='2':
        start=int(t[1])
        end=start+int(t[2])
        s=s[start:end]
        print(s)
    elif t[0]=='3':
        sta=int(t[1])
        s=s[:sta]+t[2]+s[sta:]
        print(s)
    elif t[0]=='4':
        print(s.find(t[1]))