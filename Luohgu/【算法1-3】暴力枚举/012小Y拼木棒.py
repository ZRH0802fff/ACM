import sys
data=list(map(int , sys.stdin.read().split()))
n=data[0]
tong=[0]*5010
MOD=1000000007
ans=0
for i in range(1,n+1):
    tong[data[i]]+=1
for num1 in range(1,5001):
    if tong[num1]<=1:
        continue
    a_per=(tong[num1]*(tong[num1]-1)//2)%MOD
    for num2 in range(1,num1//2+1):
        num3=num1-num2
        if num2!=num3:
            if tong[num2]>=1 and tong[num3]>=1:
                cd_pre=(tong[num2]*tong[num3])%MOD
                ans=(ans+cd_pre*a_per)%MOD
        else:
            if tong[num2]>=2:
                c_per=(tong[num2]*(tong[num2]-1)//2)%MOD
                ans=(ans+a_per*c_per)%MOD
print(ans)
