arr={}
for _ in range(int(input())):
    k,v=input().split()
    arr[k]=v
#print(arr)
print({v:k for k,v in arr.items()})