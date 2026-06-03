# import sys
# data=sys.stdin.read().split()
# n,m,k=int(data[0]),int(data[1]),int(data[2])
# graph=[list(s) for s in data[3:]]
# ans=0
# if k==1:
#     for i in range(n):
#         for j in range(m):
#             ans+=1 if graph[i][j]=='.' else 0
#     print(ans)
#     exit()
# for i in range(n):
#     for j in range(k-1,m):
#         if all(graph[i][j-x]=='.' for x in range(k)):
#             ans+=1
# for j in range(m):
#     for i in range(k-1,n):
#         if all(graph[i-x][j]=='.' for x in range(k)):
#             ans+=1
# print(ans)



"""
前缀和优化版本
用横向和竖向的前缀和数组表示前面所有障碍物的数量
来到i位置，如果  i位置的前缀和- i-k+1位置的前缀和 == k，则证明i位置前面k长度全是空地，ans++
竖向同理
"""
import sys
data=sys.stdin.read().split()
n,m,k=int(data[0]),int(data[1]),int(data[2])
graph=[list(s) for s in data[3:]]
ans=0
if k==1:
    for i in range(n):
        for j in range(m):
            ans+=1 if graph[i][j]=='.' else 0
    print(ans)
    exit()

r_sum=[[0]*(m+1) for _ in range(n+1)]
c_sum=[[0]*(m+1) for _ in range(n+1)]
for i in range(1,n+1):
    for j in  range(1,m+1):
        if graph[i-1][j-1]=='#':
            r_sum[i][j]+=1
            c_sum[i][j]+=1
        r_sum[i][j]+=r_sum[i][j-1]
        c_sum[i][j]+=c_sum[i-1][j]
for i in range(1,n+1):
    for j in range(k,m+1):
        if r_sum[i][j]-r_sum[i][j-k]==0:
            ans+=1
for j in range(1,m+1):
    for i in range(k,n+1):
        if c_sum[i][j]-c_sum[i-k][j]==0:
            ans+=1
print(ans)