import random

# 为了验证
def random_array(n, v):
    return [int(random.random() * v) + 1 for _ in range(n)]


# 为了验证（线性查找）
def right(sorted_arr, num):
    for cur in sorted_arr:
        if cur == num:
            return True
    return False

def exist (arr,num):
    if not arr :
        return False
    l,r=0,len(arr)-1
    while l<=r:
        m=(l+r)//2
        if arr[m]==num:
            return True
        elif arr[m]<num:
            l=m+1
        else:
            r=m-1
    return False

N=100
V=1000
testTime=500000

print("Test is coming")

for _ in range(testTime):
    n=int(random.random()*N)
    arr=random_array(n,V)
    arr.sort()
    num=int(random.random()*V)

    if right(arr,num)!=exist(arr,num):
        print("出错了!")
        print("arr =", arr)
        print("num =", num)
        print("right =", right(arr, num))
        print("exist =", exist(arr, num)) 
        break
print('Test is closing')