t=input().split()
s=[c.lower() for c in t]
book={
    'zero': 0,
    'one': 1,
    'two': 2,
    'three': 3,
    'four': 4,
    'five': 5,
    'six': 6,
    'seven': 7,
    'eight': 8,
    'nine': 9,
    'ten': 10,
    'eleven': 11,
    'twelve': 12,
    'thirteen': 13,
    'fourteen': 14,
    'fifteen': 15,
    'sixteen': 16,
    'seventeen': 17,
    'eighteen': 18,
    'nineteen': 19,
    'twenty': 20,
    'a': 1,           # "a" 通常表示1
    'both': 2,        # "both" 表示两者，即2
    'another': 1,     # 根据要求，another算作1处理
    'first': 1,       # "first" 第一，表示1
    'second': 2,      # "second" 第二，表示2
    'third': 3 
}
f=[]
for c in s:
    if c in book:
        f.append(book.get(c))
f=[int(c)**2 for c in f]
f.sort()
f=[f"{c:02d}" for c in f ]
ff=''.join(f).strip('0')
if ff=='':
    ff+='0'
print(ff)