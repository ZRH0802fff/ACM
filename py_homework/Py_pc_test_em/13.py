n=int(input())
arr={}
for _ in range(n):
    nm,sc=input().split()
    sc=int(sc)
    arr[nm]=sc
ma_sc=0
ma_nm=''
for k,v in arr.items():
    if v>ma_sc:
        ma_sc=v
        ma_nm=k
print(f"{ma_nm} {ma_sc}")