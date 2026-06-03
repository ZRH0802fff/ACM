arr=list(map(int ,input().split()))
arr.sort()
if arr[0]+arr[1]<=arr[2]:
    print("Not triangle")
else:
    l=arr[0]*arr[0]+arr[1]*arr[1]
    r=arr[2]*arr[2]
    if l==r:
        print("Right triangle")
    elif l>r:
        print("Acute triangle")
    elif l<r:
        print("Obtuse triangle")
    if arr[0]==arr[1] or arr[1]==arr[2]:
        print("Isosceles triangle")
        if arr[0]==arr[2]:
            print ("Equilateral triangle")