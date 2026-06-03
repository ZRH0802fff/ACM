# 暴力解法 直接模拟字符串的拼接
#
# s,idx=input().split()
# idx=int(idx)-1
# lens=len(s)
# while lens<idx:
#     lens*=2
#     s+=s[-1]+s[:-1:]

# print(s[idx])

s,idx=input().split()
idx=int(idx)
l=len(s)
while l<idx:
    i=l
    while idx>i*2:
        i*=2
    idx-=(i+1)
    if idx==0 : 
        idx=i
print(s[idx-1])