from collections import deque
n,a,b=map(int,input().split())
arr=list(map(int,input().split()))
queue=deque([a])
ge=1
ce=1
nx_ge=0
while queue:
    ge-=1
    cur=queue.popleft()
    xia=cur-arr[cur-1]
    sa=cur+arr[cur-1]
    if 1<=xia<=n:
        if xia==b:
            print(ce)
            exit()
        queue.append(xia)
        nx_ge+=1
    if 1<=sa<=n:
        if sa==b:
            print(ce)
            exit()
        queue.append(sa)
        nx_ge+=1
    if ge==0:
        ce+=1
        ge=nx_ge
        nx_ge=0
    #print(queue)
print(-1)