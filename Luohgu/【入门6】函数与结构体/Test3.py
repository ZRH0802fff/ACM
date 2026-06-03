sta,ed=map(int ,input().split())

def isLeapyear(year):
    return year%4==0 and(year%100!=0 or year%400==0)

tal=0
f=''
for i in range(sta,ed+1):
    if isLeapyear(i):
        tal+=1
        f+=str(i)+' '
print(tal)
print(f[:-1])