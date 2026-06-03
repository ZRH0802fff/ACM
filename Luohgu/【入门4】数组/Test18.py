arr=list(map(int,input().split()))
n=arr[0]
fin=[]
flag=False
for i in range(1,len(arr)):
    for t in range(arr[i]):
        fin.append(flag) 
    flag= not flag
num=0
for i in range(n):
    print("".join('1'if fin[i*n+j] else '0' for j in range(n)))
