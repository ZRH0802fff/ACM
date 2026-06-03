ans=0
for num in range(12345678,98765432):
    two1,zero,two2,three=False,False,False,False
    for ch in str(num):
        if ch=='2' and not two1:
            two1=True
        if two1 and not zero and ch=='0':
            zero=True
        if two1 and zero and not two2 and ch=='2':
            two2=True
        if two1 and zero and two2 and not three and  ch=='3':
            ans+=1
            print(f"{ans} {num}")
            continue
print(ans)