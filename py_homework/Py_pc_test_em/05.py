s=input()
tal1=tal2=tal3=0
for ch in s:
    if ch.isupper(): tal1+=1
    elif ch.islower(): tal2+=1
    else: tal3+=1
print(f"大写字母数量: {tal1}")
print(f"小写字母数量: {tal2}")
print(f"数字数量: {tal3}")