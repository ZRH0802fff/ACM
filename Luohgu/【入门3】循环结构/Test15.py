n=int(input())
arr=list(map(int,input().split()))
s,ms=1,1
for i in range(1,n):
    if arr[i]-arr[i-1]==1:
        s+=1
        if s >ms:
            ms=s
    else:
        s=1
print(ms)