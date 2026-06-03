num=int(input())
if num<0:
    num=str(num)
    print("-"+str(int(num[::-1].replace('-',''))))
else:
    num=str(num)
    print(int(num[::-1]))