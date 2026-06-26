arr=list(input().split())
ma_len=0
ma_idx=0
for i in range(len(arr)):
    tmp=len(arr[i])
    if tmp>ma_len:
        ma_len=tmp
        ma_idx=i
print(f"{arr[ma_idx]} {ma_len}")