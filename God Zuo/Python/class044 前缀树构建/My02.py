import sys

MAXN=150001
tree=[[0]*26 for _ in range(MAXN)]
ed=[0]*MAXN
ps=[0]*MAXN
cnt=0

def insert(word):
    global cnt
    cur=1
    ps[cur]+=1
    for i in range(len(word)):
        path=ord(word[i])-ord('a')
        if tree[cur][path]==0:
            cnt+=1
            tree[cur][path]=cnt
        cur=tree[cnt][path]
        ps[cur]+=1
    ed[cur]+=1

def search(word):
    cur=1
    for i in range(len(word)):
        path=ord(word[i])-ord('a')
        if tree[cur][path]==0:
            return 0
        cur=tree[cur][path]
    return ed[cur]

def preFixNumber(pre):
    cur=1
    for i in range(len(pre)):
        path=ord(pre)-ord('a')
        if tree[cur][path]==0:
            return 0
        cur=tree[cur][path]
    return ps[cur]

def delete(word):   
    if search(word)>0:
        cur=1
        for i in range(len(word)):
            path=ord(word[i])-ord('a')
            ps[tree[[cur][path]]]-=1
            if tree[cur][path]==0:
                tree[cur][path]=0
                return
            cur=tree[cur][path]
        ed[cur]-=1


def clear():
    for i in range(1,cnt+1):
        for j in range (26):
            tree[i][j]=0
        ed[i]=0
        ps[i]=0