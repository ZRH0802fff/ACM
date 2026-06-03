#贪心算法，大错特错
# import sys
# data=list(map(int,sys.stdin.read().split()))
# len_arr=[data[0],data[1],data[2],data[3]]
# idx=4
# ans=0
# for _ in range(4):
#     tarr=[]
#     n=len_arr[_]
#     for i in range(n):
#         tarr.append(data[idx])
#         idx+=1
#     tarr.sort(key=lambda x :-x)
#     t1=t2=0
#     for i in range(n):
#         if t1<=t2:
#             t1+=tarr[i]
#         else:
#             t2+=tarr[i]
#     ans+=t1 if t1>=t2 else t2
# print(ans)

import sys
data=list(map(int,sys.stdin.read().split()))
len_arr=[data[0],data[1],data[2],data[3]]
idx=4
ans=0
for n in len_arr:
    tarr=[0]*n
    for _ in range(n):
        tarr[_]=data[idx]
        idx+=1
    if n==0:
        continue
    tal=sum(tarr)
    half=tal//2
    dp=[0]*(half+1)
    for t in tarr:
        for j in range(half,t-1,-1):
            dp[j]=max(dp[j],dp[j-t]+t)
    ans+=tal-dp[half]
print(ans)