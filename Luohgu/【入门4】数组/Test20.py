sta=[]
ed=[]
old=[]
now=[]
n=0

def read():
    global n,sta,ed
    n=int(input())
    sta=[];ed=[]
    for i in range(n):
        t=list(input())
        sta.append(t)
    for i in range(n):
        t=list(input())
        ed.append(t)

def f():
    global old,now
    old=[_[:] for _ in sta ]
    now=[_[:] for _ in sta ]

def check():
    global n,now,ed
    for i in range(n):
        for j in range(n):
            if now[i][j]!=ed[i][j]:
                return False
    return True

def turn90():
    global n, now,old
    for i in range(n):
        k=n-1-i
        for j in range(n):
            now[j][k]=old[i][j]
    for i in range(n):
        for j in range(n):
            old[i][j]=now[i][j]

def turn180():
    turn90()
    turn90()

def turn270():
    turn90()
    turn90()
    turn90()

def rl():
    global n,now,old
    for i in range(n):
        j = 0
        k = n - 1
        while j <= k:
            now[i][j] = old[i][k]
            now[i][k] = old[i][j]
            j += 1
            k -= 1
    for i in range(n):
        for j in range(n):
            old[i][j] = now[i][j]

def comb():
    global n,now,old
    rl()
    turn90()
    if check():
        return True
    
    f()
    rl()
    turn180()
    if check():
        return True
    
    f()
    rl()
    turn270()
    if check():
        return True
    
    f()
    return False

read()
f()
turn90()
if check():
    print(1)
else:
    f()
    turn180()
    if check():
        print(2)
    else:
        f()
        turn270()
        if check():
            print(3)
        else:
            f()
            rl()
            if check():
                print(4)
            else:
                f()
                if comb():
                    print(5)
                else:
                    f()
                    if check():
                        print(6)
                    else:
                        print(7)