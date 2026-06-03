#暴力枚举题解，Python会超时
#每来到(i,j)点，正方形新增min(i,j)个
#矩形新增i*j个
#剩下的就是新增的长方形数量
# n,m=map(int , input().split())
# sum1=0
# sum2=0
# for i in range(n+1):
#     for j in range(m+1):
#         sum1+=i if i<j else j
#         sum2+=i*j-min(i,j)
# print(sum1,sum2)

#组合数学解法
#在n*m的矩阵中，所有矩形的数量有以下的得到方式
#从n+1条横着的线中任选两条，即 (n(n+1))//2
#从m+1条竖着的线中任选两条, 即 (m(m+1))//2
#这四条边构成矩形的四条边，即为 (n(n+1))//2*(m(m+1))//2
#正方形边长i从 1 到 min(n,m)
#i=1 时， n*m
#i=2 时， (n-1)*(m-1)
#..........
#i时 (n-i+1)*(m-i+1)

n,m=map(int , input().split())
sum1,sum2=0,0
sum=((n*(n+1))//2)*((m*(m+1))//2)
for i in range(1,min(n,m)+1):
    sum1+=(n-i+1)*(m-i+1)
sum2=sum-sum1
print(sum1,sum2)
