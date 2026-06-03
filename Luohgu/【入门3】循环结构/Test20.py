money=0
clash=0
for i in range(12):
    money+=300
    t=int(input())
    money-=t
    if money<0:
        print("-"+str(i+1))
        exit(0)
    if money>=100:
        clash+=money//100*100
        money%=100
print(int(clash*1.2+money))