# import sys
# sys.setrecursionlimit(200000)
# n=int(input())
# ans=0
# def f(i):
#     global ans
#     if i>=n:
#         if i==n:
#             ans+=1
#         return
#     f(i+1)
#     f(i+2)
# f(0)
# print(ans)
#python 纯递归会超时 可以选择挂缓存或者for 循环

#for循环法
n=int(input())
if n==1:
    print(1)
    exit()
if n==2:
    print(2)
    exit()
pre2=1
pre1=2
cur=0
for i in range(3,n+1):
    cur=pre1+pre2
    pre2=pre1
    pre1=cur
print(cur)


#挂缓存
n=int(input())
if n==1:
    print(1)
    exit()
if n==2:
    print(2)
    exit()
dp=[0]*(n+1)
dp[1],dp[2]=1,2
for i in range(3,n+1):
    dp[i]=dp[i-1]+dp[i-2]
print(dp[n])