n=int(input())
arr=list(map(int,input().split()))
total=0
book=set()
for i in range(n):
    for j in range(i+1,n):
            t=arr[i]+arr[j]
            if  t in arr and t not in book:
                  total+=1
                  book.add(t)
print(total)