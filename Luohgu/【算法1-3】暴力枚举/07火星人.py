##dfs剪枝法

import sys
sys.setrecursionlimit(20000)
data=list(map(int , sys.stdin.read().split()))
n,m=data[0],data[1]
arr=[0]+[data[i+2] for i in range(n)]
vis=[False]*(n+1)
f=[0]*(n+1)
count=0

def dfs(dp):
    global count
    if dp==n+1:
        count+=1
        if count==m+1:
            #到次数直接打印退出，而不是return ，因为return会继续往后搜索
            print(' '.join(str(_) for _ in f[1:] ))
            exit(0)
        return
    #第一个全排列生成为给定的1-n个数的顺序，再往后生成m次即可
    if count==0:
        for i in range(arr[dp],n+1):
            if vis[i]==False:
                vis[i]=True
                f[dp]=i
                dfs(dp+1)
                vis[i]=False
    else:
        for i in range(1,n+1):
            if vis[i]==False:
                vis[i]=True
                f[dp]=i
                dfs(dp+1)
                vis[i]=False

dfs(1)



###手动实现c++中的next_permutation函数
'''
=== 下一个排列 (Next Permutation) 核心逻辑 ===

目标：寻找比当前排列稍微大一点点的“下一个排列”
案例：[1, 3, 5, 4, 2]

1. 从后往前找“破绽”：
   - 寻找第一个相邻的升序对 nums[i-1] < nums[i]。
   - 案例中从后往前看：2->4 降序，4->5 降序，5->3 升序！
   - 找到破绽：数字 3 就是需要被替换的数（位置 i-1）。

2. 从后往前找“替补”：
   - 在破绽的右侧，找一个比它大、但又尽可能小的数。
   - 案例中 3 的右侧是 5, 4, 2，比 3 大且最靠右的数是 4。

3. 互换两者位置：
   - 将“破绽”与“替补”互换。
   - 案例中 3 和 4 互换，数组状态变为：[1, 4, 5, 3, 2]。

4. 尾部反转：
   - 互换后，右边区间必然是完全降序的（如 5, 3, 2）。
   - 为了保证新排列只“稍微大一点点”（增幅最小），需将其反转为升序。
   - 案例中把 5, 3, 2 反转为 2, 3, 5。
   - 最终得到结果：[1, 4, 2, 3, 5]。
'''
def nxt_pl(arr):
    n=len(arr)
    i=n-1
    while i>0 and arr[i-1]>=arr[i]:
        i-=1
    if i>0:
        j=n-1
        while arr[j]<=arr[i-1]:
            j-=1
        arr[i-1],arr[j]=arr[j],arr[i-1]
    arr[i:]=reversed(arr[i:])

for __ in range(m):
    nxt_pl(arr)
print(' '.join(str(_) for _ in arr))