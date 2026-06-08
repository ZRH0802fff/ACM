import sys
data=list(map(int , sys.stdin.read().split()))
n=data[0]
data[0]=0
tree=[0]*(4*(1<<n))
def build(idx,l,r):
    if l==r:
        tree[idx]=l
        return
    mid=(l+r)//2
    build(2*idx,l,mid)
    build(2*idx+1,mid+1,r)
    l_win=tree[2*idx]
    r_win=tree[2*idx+1]
    if data[l_win]>data[r_win]:
        tree[idx]=l_win
    else:
        tree[idx]=r_win
build(1,1,1<<n)
left_champion = tree[2]
right_champion = tree[3]

if data[left_champion] > data[right_champion]:
    print(right_champion)
else:
    print(left_champion)