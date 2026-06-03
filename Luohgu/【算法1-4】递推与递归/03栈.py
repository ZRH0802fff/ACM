# import sys
# sys.setrecursionlimit(2000000)
# # n=int(input())
# # stack=[]
# # ans=0
# # def dfs(i):
# #     global ans
# #     if i==n+1 :
# #         ans+=1
# #         return 
# #     stack.append(i)
# #     dfs(i+1)
# #     stack.pop()
# #     if len(stack)>0:
# #         t=stack.pop()
# #         dfs(i)
# #         stack.append(i)
# # dfs(1)
# # print(ans)

# def solve(n):
#     stack=[]
#     ans=0
#     def dfs(i):
#         nonlocal ans
#         if i==n+1 :
#             ans+=1
#             return 
#         stack.append(i)
#         dfs(i+1)
#         stack.pop()
#         if len(stack)>0:
#             t=stack.pop()
#             dfs(i)
#             stack.append(i)
#     dfs(1)
#     print(ans)

# for i in range(1,19):
#     solve(i)

# book=[1,2,5,14,42,132,429,1430,4862,16796,58786,208012,742900,2674440,9694845,35357670,129644790,477638700]
# print(book[int(input())-1])

#如上是dfs然后打表


n=int(input())
dp=[[0]*(n+2) for _ in range(n+2)]
for i in range(n+1):
    for j in range(n+1):
        if i==0:dp[i][j]=1
        elif j==0:dp[i][j]=dp[i-1][j+1]
        else: dp[i][j]=dp[i-1][j+1]+dp[i][j-1]
print(dp[n][0])