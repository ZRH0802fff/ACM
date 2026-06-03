import sys
arr=[0]*100010
data=list(map(int , sys.stdin.read().split()))
n=data[0]
k=data[1]
idx=2

def f(n,k):
    book={0:-1}
    ans=0
    sum=0
    for i in  range(n) :
        sum+=arr[i]
        if sum-k in book:
            ans=max(ans,i-book[sum-k])
        if  sum not in book:
            book[sum]=i
    return ans

while idx<len(data):
    for i in range (n):
        arr[i]=data[idx]
        idx+=1

print(f(n,k))