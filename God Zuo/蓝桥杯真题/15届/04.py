n=int(input())
for _ in range(n):
    t=int(input())
    ans=0
    if ans%3==0:
        ans+=2*n
    else:
        ans+=n
    print(ans)