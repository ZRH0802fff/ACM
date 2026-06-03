
# 2根：1
# 4根：4，7
# 5根：2，3，5
# 6根：0，6，9
# 7根：8
book=[6,2,5,5,4,5,6,3,7,6]
def f(num):
    if num==0: return 6
    sum=0
    while num!=0:
        sum+=book[num%10]
        num//=10
    return sum

n=int(input())
if n<13 :
    print(0)
    exit()
ans=0
for i in range(600):
    for j in range(600):
        if (f(i)+f(j)+f(i+j))+4==n:
            ans+=1
print(ans)