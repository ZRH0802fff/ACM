n=int(input())
fal=1
def f(i,num):
    global fal
    fal*=i
    if i==num:
        return fal
    return f(i+1,num)
fal=f(1,n)
print(fal)