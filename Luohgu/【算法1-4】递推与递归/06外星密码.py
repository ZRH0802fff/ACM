import sys
sys.setrecursionlimit(20000)
s=input().strip()
where=0

def f(i):
    global where
    ans=''
    op=1
    if i < len(s) and '0' <= s[i] <= '9':
        if i + 1 < len(s) and '0' <= s[i+1] <= '9':
            op = int(s[i]) * 10 + int(s[i+1])
            i += 2
        else:
            op = int(s[i])
            i += 1
    while i<len(s) and s[i]!=']':
        if 'A'<=s[i]<='Z': 
            ans+=s[i]
            i+=1
        elif s[i]=='[':
            ans+=f(i+1)
            i=where+1
        else:
            i+=1
    where=i
    return ans*op

print(f(0))