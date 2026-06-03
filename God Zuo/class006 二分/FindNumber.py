import random

N = 100             #最大数组长度
V = 1000            #数组中的最大值
testTime = 500000   #测试次数

print("测试开始")

for _ in range(testTime):
    n = int(random.random() * N)   
    arr = [int(random.random() * V) + 1 for _ in range(n)]
    arr.sort()
    num = int(random.random() * V)

    # right
    found1 = False
    for cur in arr:
        if cur == num:
            found1 = True
            break

    # exist（二分）
    found2 = False
    l, r = 0, len(arr) - 1
    while l <= r:
        m = (l + r) // 2
        if arr[m] == num:
            found2 = True
            break
        elif arr[m] > num:
            r = m - 1
        else:
            l = m + 1

    if found1 != found2:
        print("出错了!")
        break

print("测试结束")

























def f(num,arr):
    l,r=0,len(arr)-1
    while l<=r:
        m=(l+r)//2
        if arr[m]==num:
            return True
        elif arr[m]>num:
            r=m-1
        else:
            l=m+1
    return False




























