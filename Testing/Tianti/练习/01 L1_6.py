import sys

def find_arr(arr, sub, n1, n2):
    if n2 == 0:
        return -1
    if n2 > n1:
        return -1
    for i in range(n1 - n2 + 1):
        if arr[i:i+n2] == sub:
            return i
    return -1  

def f1(arr, n):
    line1 = sys.stdin.readline().split()
    n1 = int(line1[0])
    sub = list(map(int, line1[1:1+n1]))
    line2 = sys.stdin.readline().split()
    n2 = int(line2[0])
    repl = list(map(int, line2[1:1+n2]))
    
    idx = find_arr(arr, sub, len(arr), n1)
    if idx != -1:
        arr[:] = arr[:idx] + repl + arr[idx+n1:]
    return len(arr)  

def f2(arr, n):
    i = 0
    while i + 1 < len(arr):
        if (arr[i]+arr[i+1])%2==0 :
            arr.insert(i+1, (arr[i] + arr[i+1]) // 2)
            i += 2 
        else:
            i += 1 
    return len(arr)

def f3(arr, n):
    l, r = map(int, sys.stdin.readline().split())
    arr[l:r+1]=arr[l:r+1][::-1]
    return len(arr)

n, m = map(int, sys.stdin.readline().split())
arr = list(map(int, sys.stdin.readline().split()))
print(arr)
print(' '.join("%2d" %i for i in range(44)))
for _ in range(m):
    cz = int(sys.stdin.readline())
    if cz == 1:
        f1(arr, len(arr))
    elif cz == 2:
        f2(arr, len(arr))
    else:
        f3(arr, len(arr))

    print(' '.join("%2d" %i for i in arr))

#14 9 2 21 8 21  9 10 21  5  4  5 14  1 26  8  5 14  4  5  2 21 19  8  9 26  9  6 21  3  8 21  1 14 20  9  2  1
#14 9 2 21 8 21  9 10 21  5  4  5 14  1 26  8  5 14  4  5  2 21 19  8  9 26  9  6 21  3  8 21  1 14 20  9  1  2
#14 9 2 21 8 21  9 10 21  5  4  5 14  1 26  8  5 14  4  5  2 21 19  8  9  1  2  3  4  5  6  7  8  9 10 11 12 13 14  1  2
#14 9 2 21 8 21 15  9 10 21 13  5  4  5 14  1 26 17  8  5 14  9  4  5  2 21 20 19  8  9  5  1  2  3  4  5  6  7  8  9 10 11 12 13 14 1 2
#14 9 8  7 6  5  4  3  2  1  5  9  8 19 20 21  2  5  4  9 14  5  8 17 26  1 14  5  4  5 13 21 10  9 15 21  8 21  2  9 10 11 12 13 14 1 2
#0  1 2  3 4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43