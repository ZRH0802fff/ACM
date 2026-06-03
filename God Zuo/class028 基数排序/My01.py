import sys

BASE=10
MAXN=100001
arr=[0]*MAXN
helparr=[0]*MAXN
cnts=[0]*BASE
n=0

def radix_sort(bits_count):
    office=1
    while bits_count>0:
        cnts[:]=[0]*BASE
        for i in range(n):
            cnts[(arr[i]//office)%BASE]+=1
        for i in range(1,BASE):
            cnts[i]+=cnts[i-1]
        for i in range (n-1,-1,-1):
             digit=(arr[i]//office)%BASE
             cnts[digit]-=1
             helparr[cnts[digit]]=arr[i]
        arr[:]=helparr[:n]
        office*=BASE
        bits_count-=1

def sort_arr():
    min_val=arr[0]
    for i in range(1,n):
        min_val=min(arr[i],min_val)
    max_val=0
    for i in range(0,n):
        arr[i]-=min_val
        max_val=max(arr[i],max_val)
    radix_sort(bits(max_val))
    for i in range(n):
        arr[i]+=min_val

def bits(num):
    ans=0
    while num>0:
        num//=BASE
        ans+=1
    return ans

data=sys.stdin.read().split()
n=int(data[0])
idx=1
for i in range(n):
    arr[i]=int(data[idx])
    idx+=1
sort_arr()
print(' '.join(str(arr[i])for i in range(n)))