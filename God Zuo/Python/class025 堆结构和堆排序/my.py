import sys

MAXN=100001
arr=[0]*MAXN
n=0

def swap(i,j):
    arr[i],arr[j]=arr[j],arr[i]

def heapInsert(i):
    while arr[i]>arr[(i-1)//2]:
        swap(i,(i-1)//2)
        i=(i-1)//2

def heapifay(i,size):
    l=i*2+1
    while l<size:
        best=l+1 if l+1<size and arr[l+1]>arr[l] else l
        best= best if arr[best]>arr[i] else i
        if best ==i:
            break
        swap(best,i)
        i=best
        l=i*2+1

def heapsort1():
    for i in range (0,n):
        heapInsert(i)
    size=n
    while size>1:
        size-=1
        swap(0,size)
        heapifay(0,size)
    
def heapsort2():
    for i in range(n-1,-1,-1):
        heapifay(i,n)
    size=n
    while size>1:
        size-=1
        swap(0,size)
        heapifay(0,size)

data=sys.stdin.read().split()
idx=0
n=int(data[idx])
idx+=1
for i in range(n):
    arr[i]=int(data[idx])
    idx+=1
heapsort2()
print(' '.join(str(arr[i]) for i in range(0,n)))
    
