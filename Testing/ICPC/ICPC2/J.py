import sys
arr=['A','B','C','D','E','F','G','H','I','J','K','L']
book={'WrongProblem':100,'SameProblem':30,'UnreasonableLimitForProblem':5,'WeakTestsForProblem':3,'BadProblem':1}

data=sys.stdin.read().split()
T=int(data[0])
idx=1
for _ in range(T):
    n=int(data[idx])
    p=int(data[idx+1])
    idx+=2
    ans=0
    for i in range (n):
        s=data[idx]
        idx+=1
        if s=='UnreasonableProblemArrangement' :
            ans+=10
        elif s[-1] in arr:
            if s[:-1:] in book:
                ans+=book[s[:-1:]]
    if ans>p:
        print('Joker')
    else:
        print('Judger')
