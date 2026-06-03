import sys
data=list(map(int , sys.stdin.read().split()))
n=data[0]
idx=1
arr=[0]*n
for i in range(n):
    arr[i]=data[idx]
    idx+=1
larr=[0]*n
rarr=[0]*n
stack=[]
for i in range(n):
    while stack and arr[stack[-1]]>=arr[i]:
        cur=stack.pop()
        larr[cur]=stack[-1] if stack else -1
        rarr[cur]=i
    stack.append(i)

while stack:
    cur=stack.pop()
    rarr[cur]=-1
    larr[cur]=stack[-1] if stack else -1

for i in range(n-2 ,-1,-1):
    if rarr[i]!= -1 and arr[i]== arr[rarr[i]]:
        rarr[i]=rarr[rarr[i]]
out=[]
for i in range(n):
    out.append(f"{larr[i]} {rarr[i]}")
sys.stdout.write('\n'.join(out) + '\n')   