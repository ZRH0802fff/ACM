# 测试链接 : https://www.luogu.com.cn/problem/P4799
import sys
data=list(map(int,sys.stdin.read().split()))
n,w=data[0],data[1]
idx=2
arr = [x for x in data[2 : n+2]]
arr.sort()
mid = n >> 1
left_arr = arr[::2]
right_arr = arr[1::2]
lsum=[0]
for val in left_arr:
    lsum.extend([s+val for s in lsum if s+val<=w])
rsum=[0]
for val in right_arr:
    rsum.extend([s+val for s in rsum if s+val<=w])
lsum.sort(reverse=True)
rsum.sort()
ans=0
j=0
rlen=len(rsum)
for val in lsum:
    while j<rlen and val+rsum[j]<=w:
        j+=1
    ans+=j
print(ans)