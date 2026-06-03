import math

arr=list(map(int ,input().split()))
arr.sort()
gcd=math.gcd(arr[0],arr[2])
a=int(arr[0]/gcd)
b=int(arr[2]/gcd)
print(f"{a}/{b}")