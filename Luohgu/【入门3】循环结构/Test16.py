
n=int(input())

if n==1:
    print(1)
    exit(0)
for i in range(2,n+1):
    if n%i==0:
        print(int(n/i))
        break