n=int(input())
arr=[]
for i in range(n):
    t=list(map(int,input().split()))
    arr.append(t)

def isHao(i,j):
    if abs(arr[i][0]-arr[j][0])<=5 and abs(arr[i][1]-arr[j][1])<=5 and abs(arr[i][2]-arr[j][2])<=5:
        sum1=arr[i][0]+arr[i][1]+arr[i][2]
        sum2=arr[j][0]+arr[j][1]+arr[j][2]
        if abs(sum1-sum2)<=10:
            return True
    return False

total=0
for i in range(0,n):
    for j in range(i+1,n):
        if isHao(i,j):
            total+=1
print(total)
    