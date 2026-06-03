arr=list(map(int,input().split()))
shunxu=input().strip()
arr.sort()
mapping={
    'A':arr[0],
    'B':arr[1],
    'C':arr[2]
}
result=[]
for char in shunxu:
    result.append(str(mapping[char]))
print(' '.join(result))