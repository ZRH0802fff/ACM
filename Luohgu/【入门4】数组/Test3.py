n=int(input())
arr=[n]
while n!=1:
    if n%2==0:
        n/=2
        arr.append(int(n))
    else:
        n=n*3+1
        arr.append(int(n))
arr.reverse()
f=" ".join(map(str,arr))
print(f)