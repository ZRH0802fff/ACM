s=input()
if '.' in s:
    t=s.find('.')
    s1=s[:t].rstrip('0')
    s2=s[t+1:].lstrip('0')
    if s1=='':
        s1+='0'
    if s2=='':
        s2+='0'
    f=s1[::-1]+'.'+s2[::-1]
    print(f)
elif '/' in s :
    t=s.find('/')
    s1=s[:t].rstrip('0')
    s2=s[t+1:].rstrip('0')
    if s1=='':
        s1+='0'
    if s2=='':
        s2+='0'
    f=s1[::-1]+'/'+s2[::-1]
    print(f)
elif '%'in s:
    t=s[:-1][::-1]
    f=t.lstrip('0')
    if f=='':
        f+='0'
    print(f+'%')
else:
    t=s[::-1]
    f=t.lstrip('0')
    if f=='':
        f+='0'
    print(f)