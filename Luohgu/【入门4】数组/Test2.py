arr=list(map(int,input().split()))
f=""
for i in range(len(arr)-2,-1,-1):
    f=f+str(arr[i])+" "
print(f)