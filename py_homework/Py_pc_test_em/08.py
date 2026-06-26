arr1=set(list(map(int,input().split())))
arr2=set(list(map(int,input().split())))

print(f"交集: {sorted(arr1.intersection(arr2))}")
print(f"并集: {sorted(arr1.union(arr2))}")