import sys

data=list(map(int , sys.stdin.read().split()))
n,d=data[0],data[1]
idx=2
arr=[]
for _ in range(n):
    arr.append((data[idx],data[idx+1]))
    idx+=2
arr.sort(key=lambda x : x[0])
max_q=[0]*n
min_q=[0]*n
max_h=max_t=min_h=min_t=0

def ok():
    max_val = arr[max_q[max_h]][1] if max_h < max_t else 0
    min_val = arr[min_q[min_h]][1] if min_h < min_t else 0
    return max_val - min_val >= d

def push(r):
    global max_t, min_t
    while max_h<max_t and arr[max_q[max_t-1]][1]<=arr[r][1]:
        max_t-=1
    max_q[max_t]=r
    max_t+=1
    while min_h<min_t and arr[min_q[min_t-1]][1]>=arr[r][1]:
        min_t-=1
    min_q[min_t]=r
    min_t+=1

def pop(l):
    global max_h, min_h
    if max_h < max_t and max_q[max_h] == l:
        max_h += 1
    if min_h < min_t and min_q[min_h] == l:
        min_h += 1
ans=float('inf')
r=0
for l in range(n):
    while not ok() and r<n:
        push(r)
        r+=1
    if ok():
        ans= ans if ans <arr[r-1][0]-arr[l][0] else arr[r-1][0]-arr[l][0]
    pop(l)

if ans == float('inf'):
    print(-1)
else:
    print(ans)
