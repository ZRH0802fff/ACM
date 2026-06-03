x,n=map(int ,input().split())
z=n//7
yu=n%7
f=z*5*250
for i in range(yu):
    day=(x+i-1)%7+1
    if day<=5:
        f+=250
print(f)